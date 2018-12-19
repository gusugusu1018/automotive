#include <iostream>
#include <string>
#include <cmath>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>

typedef pcl::PointXYZ XYZ;

Eigen::Matrix4f calcMatrix(std::string _path, int _idx) {
	std::string jsonFile = _path + std::to_string(_idx) + "_pose.json";
	boost::property_tree::ptree pt;
	read_json(jsonFile, pt);
	boost::optional<float> px,py,pz,qx,qy,qz,qw;
	if (!(px = pt.get_optional<float>("Pose.translation.x"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(py = pt.get_optional<float>("Pose.translation.y"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(pz = pt.get_optional<float>("Pose.translation.z"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qx = pt.get_optional<float>("Pose.unit_quaternion.x"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qy = pt.get_optional<float>("Pose.unit_quaternion.y"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qz = pt.get_optional<float>("Pose.unit_quaternion.z"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qw = pt.get_optional<float>("Pose.unit_quaternion.w"))) {
		std::cout << "value is nothing" << std::endl;
	}
	_idx++;
	jsonFile = _path + std::to_string(_idx) + "_pose.json";
	read_json(jsonFile, pt);
	boost::optional<float> px2,py2,pz2,qx2,qy2,qz2,qw2;
	if (!(px2 = pt.get_optional<float>("Pose.translation.x"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(py2 = pt.get_optional<float>("Pose.translation.y"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(pz2 = pt.get_optional<float>("Pose.translation.z"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qx2 = pt.get_optional<float>("Pose.unit_quaternion.x"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qy2 = pt.get_optional<float>("Pose.unit_quaternion.y"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qz2 = pt.get_optional<float>("Pose.unit_quaternion.z"))) {
		std::cout << "value is nothing" << std::endl;
	}
	if (!(qw2 = pt.get_optional<float>("Pose.unit_quaternion.w"))) {
		std::cout << "value is nothing" << std::endl;
	}
	float dpx = px.get() - px2.get();
	float dpy = py.get() - py2.get();
	float dpz = pz.get() - pz2.get();
	float distance = sqrt(pow(qx.get(),2) + pow(qy.get(),2) + pow(qz.get(),2));
	float nqx = qx.get()/distance;
	float nqy = qy.get()/distance;
	float nqz = qz.get()/distance;
	float nqw = cosf(qw.get());
	float distance2 = sqrt(pow(qx2.get(),2) + pow(qy2.get(),2) + pow(qz2.get(),2));
	float nqx2 = qx2.get()/distance2;
	float nqy2 = qy2.get()/distance2;
	float nqz2 = qz2.get()/distance2;
	float nqw2 = cosf(qw2.get());
	float dqx = nqx - nqx2;
	float dqy = nqy - nqy2;
	float dqz = nqz - nqz2;
	float dqw = nqw - nqw2;
	Eigen::Matrix4f matrix;
	matrix <<
		1.0f-2*pow(dqy,2)-2*pow(dqz,2), 2*dqx*dqy+2*dqw*dqz, 2*dqx*dqz-2*dqw*dqy, dpx,
		2*dqx*dqy-2*dqw*dqz, 1.0f-2*pow(dqx,2)-2*pow(dqz,2), 2*dqy*dqz+2*dqw*dqx, dpy,
		2*dqx*dqz+2*dqw*dqy, 2*dqy*dqz-2*dqw*dqx, 1.0f-2*pow(dqx,2)-2*pow(dqy,2), dpz,
		0.0, 0.0, 0.0, 1.0;
	/*
	matrix <<
		1.0, 0.0, 0.0, dpx,
		0.0, 1.0, 0.0, dpy,
		0.0, 0.0, 1.0, dpz,
		0.0, 0.0, 0.0, 0.0;
	*/
	return matrix;
}

int main(int argc, char *argv[]){
	const int waitTime = 100;
	pcl::PointCloud<XYZ>::Ptr cloud (new pcl::PointCloud<XYZ>);
	pcl::PointCloud<XYZ>::Ptr cloud2 (new pcl::PointCloud<XYZ>);
	pcl::PointCloud<XYZ>::Ptr cloud3 (new pcl::PointCloud<XYZ>);
	std::string jsonPath = "../../../dataset/dataset1/bike_bicycle[5]/1/pose/";
	std::string pcdPath = "../../../pcd/";

	int cloudIdx = 0;
	std::string pcdFile = pcdPath + std::to_string(cloudIdx) + ".pcd";
	if( pcl::io::loadPCDFile (pcdFile, *cloud)){
		std::cout << "Load was failed." << std::endl;
		return -1;
	}
	Eigen::Matrix4f transformMatrix = calcMatrix(jsonPath,cloudIdx);
	cloudIdx = 1;
	pcdFile = pcdPath + std::to_string(cloudIdx) + ".pcd";
	if( pcl::io::loadPCDFile (pcdFile, *cloud2)){
		std::cout << "Load was failed." << std::endl;
		return -1;
	}
	pcl::transformPointCloud(*cloud2, *cloud3, transformMatrix);

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("Serial PCD Visualizer"));
	viewer->setBackgroundColor (0, 0, 0);
	viewer->addCoordinateSystem (10);
	viewer->addText("cloudIdx: " + std::to_string(cloudIdx), 10, 10, "cloudIdx");
	pcl::visualization::PointCloudColorHandlerCustom<XYZ> color(cloud, 0, 0, 255);
	viewer->addPointCloud<XYZ> (cloud, color, "cloud");
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	//pcl::visualization::PointCloudColorHandlerCustom<XYZ> color2(cloud, 0, 255, 0);
	//viewer->addPointCloud<XYZ> (cloud2, color2, "cloud2");
	//viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud2");
	pcl::visualization::PointCloudColorHandlerCustom<XYZ> color3(cloud, 255, 0, 0);
	viewer->addPointCloud<XYZ> (cloud3, color3, "cloud3");
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud3");
	while (!viewer->wasStopped()){
		viewer->spinOnce(waitTime);
	}
	return 0;
}

