#include <iostream>
#include <string>
#include <cstdio>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
/*
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZ XYZ;
typedef pcl::PointXYZRGB RGB;
 */

int main(int argc, char *argv[]){
	std::string jsonPath = "../../../dataset/dataset1/bike_bicycle[5]/1/pose/";
	std::string jsonFile = jsonPath + "0_pose.json";
	boost::property_tree::ptree pt;
	read_json(jsonFile, pt);
	float x,x2;
	if (boost::optional<float> xvalue = pt.get_optional<float>("Pose.translation.x")) {
		std::cout << "value : " << xvalue.get() << std::endl;
		x = xvalue.get();
	} else {
		std::cout << "value is nothing" << std::endl;
		return -1;
	}
	jsonFile = jsonPath + "1_pose.json";
	read_json(jsonFile, pt);
	if (boost::optional<float> xvalue2 = pt.get_optional<float>("Pose.translation.x")) {
		std::cout << "value : " << xvalue2.get() << std::endl;
		x2 = xvalue2.get();
	} else {
		std::cout << "value is nothing" << std::endl;
		return -1;
	}
	float diff = x - x2;

	Eigen::Matrix4f transform_matrix;
	transform_matrix <<
        	1.0, 0.0, 0.0, ,
        	0.0, 1.0, 0.0, ,
        	0.0, 0.0, 1.0, ,
        	0.0, 0.0, 0.0, 0.0;
	/*
	   const int waitTime = 1000;
	   std::cout << argv[0] << std::endl;
	   std::string filename;
	   std::string filebase = argv[1];
	   std::string identifier (".pcd");
	   bool loadSuccess = false;
	   boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("Serial PCD Visualizer"));
	   int cloudIdx = 0;
	   pcl::PointCloud<XYZ>::Ptr cloud (new pcl::PointCloud<XYZ>);
	   filename = filebase + std::to_string(cloudIdx) + identifier;
	   if( pcl::io::loadPCDFile (filename, *cloud)){
	   std::cout << "Load was failed." << std::endl;
	   return -1;
	   }
	   cloudIdx = 1;
	   pcl::PointCloud<XYZ>::Ptr cloud2 (new pcl::PointCloud<XYZ>);
	   filename = filebase + std::to_string(cloudIdx) + identifier;
	   if( pcl::io::loadPCDFile (filename, *cloud2)){
	   std::cout << "Load was failed." << std::endl;
	   return -1;
	   }
	   viewer->setBackgroundColor (0, 0, 0);
	   viewer->addCoordinateSystem (10);
	   viewer->addText("cloudIdx: " + std::to_string(cloudIdx), 10, 10, "cloudIdx");
	   pcl::visualization::PointCloudColorHandlerCustom<XYZ> color(cloud, 0, 0, 255);
	   viewer->addPointCloud<XYZ> (cloud, color, "cloud");
	   viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	   pcl::visualization::PointCloudColorHandlerCustom<XYZ> color2(cloud, 0, 255, 0);
	   viewer->addPointCloud<XYZ> (cloud2, color2, "cloud2");
	   viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud2");
	   while (!viewer->wasStopped()){
	   viewer->spinOnce(waitTime);
	   }
	   return 0;
	 */
}

