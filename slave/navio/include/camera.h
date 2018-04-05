#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/opencv.hpp>

class NetCamera {
private:
	cv::VideoCapture cap;

public:
	NetCamera() : cap(0) {
	}

	void update() {

	}
};

#endif
