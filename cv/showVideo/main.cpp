#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

int main (int argc, char** argv) {
	std::cout << argv[0] << std::endl;
	std::string filename = argv[1];
	cv::VideoCapture capture = cv::VideoCapture(filename);
	cv::Mat Mat;
	capture >> Mat;
	if (Mat.empty()) {
		std::cout << filename << " not found" << std::endl;
		return -1;
	}
	while (cv::waitKey(1000) == -1) {
		capture >> Mat;
		if (Mat.empty()) {
			std::cout << "Finish" << std::endl;
			capture.release();
			return 0;
		}
		cv::imshow(filename, Mat);
	}
	capture.release();
	return 0;
}

