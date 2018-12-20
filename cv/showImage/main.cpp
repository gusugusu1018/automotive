#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char** argv) {
	std::cout << argv[0] << std::endl;
	std::string filename = argv[1];
	const int loadFlag = CV_LOAD_IMAGE_ANYDEPTH;// COLOR // GRAYSCALE
	cv::Mat srcMat = cv::imread(filename, loadFlag);
	if (srcMat.empty()) {
		std::cout << filename << " not found" << std::endl;
		return -1;
	}
	cv::imshow(filename, srcMat);
	cv::waitKey(0);
	return 0;
}

