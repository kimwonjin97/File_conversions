#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>
#include <rosbag/bag.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
int main(int argc, char** argv){

    
    
    string const str1 = "directory/of/the/file/here";
    string const str2 = ".txt";
    

    for(int i=10; i<=96; i++){
        pcl::PointCloud<pcl::PointXYZI> cloud;
        std::string filename;
        std::stringstream ss;
        ss << i;
        filename = str1 + ss.str() + str2; //actual directory of file in the folder (for example: /home/kimw56751/Desktop/sr-test-data/1.pcd). 
        std::cout << filename << std::endl;

        string x, y, z, intensity;
        vector<float> x_val;
        vector<float> y_val;
        vector<float> z_val;
        vector<float> intensity_val;


        int line_count = 0;

        
        fstream inputFile(filename, ios_base::in | ios_base::out);

        if(inputFile.is_open()){
            
            while(!inputFile.eof()){
                inputFile >> x;
                //getline(inputFile, x, ',');
                x_val.push_back(stof(x));
                inputFile >> y;
                //getline(inputFile, y, ',');
                y_val.push_back(stof(y));
                inputFile >> z;
                //getline(inputFile, z, ',');
                z_val.push_back(stof(z));
                inputFile >> intensity;
                //getline(inputFile, intensity, '\n');
                intensity_val.push_back(stof(intensity));
                line_count++;
            }
            inputFile.close();
            line_count--;
        }
        cloud.width = line_count;
        cloud.height = 1;
        cloud.is_dense = false;
        cloud.points.resize(cloud.width * cloud.height);
        for(int i=0; i<line_count; ++i){
            cloud.points[i].x = x_val[i];
            cloud.points[i].y = y_val[i];
            cloud.points[i].z = z_val[i];
            cloud.points[i].intensity = intensity_val[i];
        }
        string savedfilename = "test"+ss.str()+".pcd";
        pcl::io::savePCDFileASCII ("test"+ss.str()+".pcd", cloud);
    }



}