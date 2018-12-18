#include <iostream>
#include <string>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/console/parse.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>

typedef pcl::PointXYZ PointType;

int main(int argc, char *argv[]){
//  pcl::PointCloud<PointType>::Ptr cloud (new pcl::PointCloud<PointType>);
  pcl::PointCloud<PointType>::Ptr cloud (new pcl::PointCloud<PointType>);
  std::string filename;
//  std::string filepath ("../../dataset/");
//  std::string filebase ("pcap");
  std::string filebase = argv[1];
  std::string identifier (".pcd");
  int could_not_pcd_times = 1;

  pcl::visualization::CloudViewer viewer("cloud viewer");

  int i = 0;
  while (!viewer.wasStopped()){
//    filename = filepath + filebase + std::to_string(i) + identifier;
    filename = filebase + std::to_string(i) + identifier;
    if( !pcl::io::loadPCDFile (filename, *cloud)){
      std::cout << filename << " was loaded." << std::endl;
      could_not_pcd_times = 0;
    }else{
      if (could_not_pcd_times == 0){
        i = 0;
        could_not_pcd_times = 1;
      }else{
        std::cout << "Load was failed." << std::endl;
        return -1;
      }
    }
    i++;
    viewer.showCloud(cloud);
    std::cout << i << std::endl;
  }
  return 0;
}

