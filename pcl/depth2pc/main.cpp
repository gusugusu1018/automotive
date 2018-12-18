#include "main.hpp"

int main (int argc, char** argv)
{
	if (pcl::console::find_argument (argc, argv, "-h") >= 0) {
		printUsage (argv[0]);
		return 0;
	}
	float LIDAR_HEIGHT = 1.4f;
	if (pcl::console::find_argument (argc, argv, "-zthresh") >= 0) {
		LIDAR_HEIGHT = std::stof(argv[2]);
	}
	std::cout << "z thresh : " << std::to_string(LIDAR_HEIGHT) << std::endl;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("My Viewer"));
	const std::string DEPTH_IMG_PATH = "../../../depth/";
	const std::string NORMAL_IMG_PATH = "../../../normal/";
	const int IMG_HEIGHT = 64;
	const int IMG_WIDTH = 2048;
	const int PICNUMS = 50;
	const int NORMAL_THRESH = 192;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	int picNum = 0;
	//for (int picNum = 0; picNum < PICNUMS; picNum++){
	std::string depthFile = DEPTH_IMG_PATH + std::to_string(picNum) + "_depth.png";
	cv::Mat depthImg = cv::imread(depthFile, CV_LOAD_IMAGE_ANYDEPTH);
	if(depthImg.empty()) {
		std::cout << "depthImg empty" << std::endl;
		return -1;
	}
	std::string normalFile = NORMAL_IMG_PATH + std::to_string(picNum) + "_normal.png";
	cv::Mat normalImg = cv::imread(normalFile, CV_LOAD_IMAGE_COLOR);
	if(normalImg.empty()) {
		std::cout << "normalImg empty" << std::endl;
		return -1;
	}
	std::string ty =  type2str(depthImg.type());
	std::cout << "Open File : " << depthFile 
		<< " Matrix: (" << ty.c_str()
		<< ", " << std::to_string(depthImg.cols)
		<< ", " << std::to_string(depthImg.rows) 
		<< ")" << std::endl;
	ty =  type2str( normalImg.type() );
	std::cout << "Open File : " << normalFile 
		<< " Matrix: (" << ty.c_str()
		<< ", " << std::to_string(normalImg.cols)
		<< ", " << std::to_string(normalImg.rows) 
		<< ")" << std::endl;
	for (int h = 0; h < IMG_HEIGHT; h++) {
		for (int w = 0; w < IMG_WIDTH; w++) {
			if (depthImg.at<unsigned char> (h,w) != 0) {
				float r = float(depthImg.at<unsigned char>(h,w)) / 655.36f;
				float theta = float(w) * M_PI / 1024.0f; 
				float phi;
				if (h < 32) {
					phi = (2.0f - float(h) / 3.0f) * M_PI / 180.0f;
				} else {
					phi = (- 8.33f - float(h - 31)/2.0f) * M_PI / 180.0f;
				}
				if ((r * sinf(phi) > - LIDAR_HEIGHT * 0.1f) && (normalImg.at<unsigned char>(h,w,0) < NORMAL_THRESH)) {
					pcl::PointXYZ point;
					point.x = r * cosf(theta) * cosf(phi);
					point.y = r * sinf(theta) * cosf(phi);
					point.z = r * sinf(phi);
					cloud->points.push_back(point);
				}
			}
		}
	}
	const std::string pcdFile = "../pcd/" + std::to_string(picNum) + ".pcd";
	pcl::io::savePCDFileBinary(pcdFile, *cloud);
	//}
	cv::namedWindow("Image", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::imshow("Image", depthImg);
	viewer->setBackgroundColor (0, 0, 0);
	viewer->addCoordinateSystem (0.1);
	int cloudIdx = 0;
	viewer->addPointCloud<pcl::PointXYZ> (cloud, std::to_string(cloudIdx));
	viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, std::to_string(cloudIdx));
	viewer->initCameraParameters ();
	viewer->addText("cloudIdx: " + std::to_string(cloudIdx), 10, 10);
	while (!viewer->wasStopped ()) {
		viewer->spinOnce (100);
		boost::this_thread::sleep (boost::posix_time::microseconds (100000));
	}
}
