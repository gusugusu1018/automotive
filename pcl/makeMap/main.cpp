#include "main.hpp"

pcl::PointCloud<XYZ>::Ptr cloud (new pcl::PointCloud<XYZ>);
pcl::PointCloud<XYZ>::Ptr nextCloud (new pcl::PointCloud<XYZ>);
int cloudIdx;
const std::string jsonPath = "../../../dataset/dataset1/bike_bicycle[5]/1/pose/";
const std::string pcdPath = "../../../pcd/";

void keyboardEventOccurred (const pcl::visualization::KeyboardEvent &event, void* viewer_void) {
	pcl::visualization::PCLVisualizer *viewer = static_cast<pcl::visualization::PCLVisualizer *> (viewer_void);
	if (event.getKeySym() == "r" && event.keyDown()) {
		std::cout << "next" << std::endl;
		*cloud = *cloud + *nextCloud;
		Eigen::Matrix4f transformMatrix = calcMatrix(jsonPath,cloudIdx);
		cloudIdx++;
		std::string pcdFile = pcdPath + std::to_string(cloudIdx) + ".pcd";
		if( pcl::io::loadPCDFile(pcdFile, *nextCloud)) {
			std::cout << "Load was failed." << std::endl;
		}
		pcl::transformPointCloud(*cloud, *cloud, transformMatrix);
	}
}

int main(int argc, char *argv[]){
	cloudIdx = 0;
	std::string pcdFile = pcdPath + std::to_string(cloudIdx) + ".pcd";
	if( pcl::io::loadPCDFile(pcdFile, *cloud)){
		std::cout << "Load was failed." << std::endl;
		return -1;
	}

	Eigen::Matrix4f transformMatrix = calcMatrix(jsonPath,cloudIdx);

	cloudIdx++;
	pcdFile = pcdPath + std::to_string(cloudIdx) + ".pcd";
	if( pcl::io::loadPCDFile(pcdFile, *nextCloud)){
		std::cout << "Load was failed." << std::endl;
		return -1;
	}
	pcl::transformPointCloud(*cloud, *cloud, transformMatrix);

	const int waitTime = 100;

	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("Serial PCD Visualizer"));
	viewer->setBackgroundColor (0, 0, 0);
	viewer->addCoordinateSystem (10);
	viewer->addText("cloudIdx: " + std::to_string(cloudIdx), 10, 10, "cloudIdx");
	pcl::visualization::PointCloudColorHandlerCustom<XYZ> color(cloud, 0, 0, 255);
	viewer->addPointCloud<XYZ> (cloud, color, "cloud");
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	pcl::visualization::PointCloudColorHandlerCustom<XYZ> color2(cloud, 0, 255, 0);
	viewer->addPointCloud<XYZ> (nextCloud, color2, "nextCloud");
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "nextCloud");
	viewer->registerKeyboardCallback (keyboardEventOccurred, (void*)viewer.get());
	while (!viewer->wasStopped()){
		viewer->spinOnce(waitTime);
		viewer->updateText("cloudIdx: " + std::to_string(cloudIdx), 10, 10, "cloudIdx");
		viewer->updatePointCloud<pcl::PointXYZ> (cloud, color, "cloud");
		viewer->updatePointCloud<pcl::PointXYZ> (nextCloud, color2,"nextCloud");
	}
	return 0;
}

