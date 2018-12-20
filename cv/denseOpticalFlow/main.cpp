#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/superres/optical_flow.hpp>

int main (int argc, char** argv) {
	std::cout << argv[0] << std::endl;
	std::string filename = argv[1];
	cv::VideoCapture capture = cv::VideoCapture(filename);
	cv::Ptr<cv::superres::DenseOpticalFlowExt> opticalFlow = cv::superres::createOptFlow_DualTVL1();
	cv::Mat prev;
	capture >> prev;
	if (prev.empty()) {
		std::cout << filename << " not found" << std::endl;
		return -1;
	}
	int idx = 0;
	while (true) {
		std::cout << idx << std::endl;
		cv::Mat curr;
		capture >> curr;
		if (curr.empty()) {
			std::cout << "Finish" << std::endl;
			capture.release();
			return 0;
		}
		cv::Mat flowX, flowY;
		opticalFlow->calc(prev, curr, flowX, flowY);
		cv::Mat magnitude, angle;
		cv::cartToPolar(flowX, flowY, magnitude, angle, true);
		cv::Mat hsvPlanes[3];		
		hsvPlanes[0] = angle;
		cv::normalize(magnitude, magnitude, 0, 1, cv::NORM_MINMAX);
		hsvPlanes[1] = magnitude;
		hsvPlanes[2] = cv::Mat::ones(magnitude.size(), CV_32F);
		cv::Mat hsv;
		cv::merge(hsvPlanes, 3, hsv);
		cv::Mat flowBgr;
		cv::cvtColor(hsv, flowBgr, cv::COLOR_HSV2BGR);
		cv::imshow("optical flow", flowBgr);
		prev = curr;
		idx++;
		cv::waitKey(0);
	}
	capture.release();
	return(0);
}
