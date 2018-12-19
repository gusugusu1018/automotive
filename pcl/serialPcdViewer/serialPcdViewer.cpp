#include <iostream>
#include <string>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/console/parse.h>
#include <pcl/visualization/pcl_visualizer.h>

void printUsage (const char* progName)
{
  std::cout << "\n\nUsage: "<<progName<<" [options]\n\n"
            << "Options:\n"
            << "-------------------------------------------\n"
            << "-h           this help\n"
            << "-n           millisec\n"
            << "./serialPcdVisualizer PCD_FILE_DIRECTORY -n 100\n"
            << "\n\n";
}

int main(int argc, char *argv[]){
	if (pcl::console::find_argument (argc, argv, "-h") >= 0) {
		printUsage (argv[0]);
		return 0;
	}
	int waitTime = 100;
	if (pcl::console::find_argument (argc, argv, "-n") >= 0) {
		waitTime = std::stoi(argv[3]);
		std::cout << "set waitTime " << argv[3] << "millisec" << std::endl;
	}
	std::cout << argv[0] << std::endl;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	std::string filename;
	std::string filebase = argv[1];
	std::string identifier (".pcd");
	bool loadSuccess = false;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("Serial PCD Visualizer"));
	int cloudIdx = 0;
	viewer->setBackgroundColor (0, 0, 0);
	viewer->addCoordinateSystem (10);
	viewer->addText("cloudIdx: " + std::to_string(cloudIdx), 10, 10, "cloudIdx");
	viewer->addPointCloud<pcl::PointXYZ> (cloud, "cloud");
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
	while (!viewer->wasStopped()){
		filename = filebase + std::to_string(cloudIdx) + identifier;
		if( !pcl::io::loadPCDFile (filename, *cloud)){
			loadSuccess = true;
		}else{
			if (loadSuccess){
				cloudIdx = 0;
				loadSuccess = false;
			}else{
				std::cout << "Load was failed." << std::endl;
				return -1;
			}
		}
		cloudIdx++;
		viewer->updateText("cloudIdx: " + std::to_string(cloudIdx), 10, 10, "cloudIdx");
		viewer->updatePointCloud<pcl::PointXYZ> (cloud, "cloud");
		viewer->spinOnce(waitTime);
	}
	return 0;
}

