#pragma once

#include <opencv2/opencv.hpp>

namespace camera {

class NetCamera {
private:
	cv::VideoCapture cap;

public:
	NetCamera() : cap(0) {
	}

	void update() {

	}
};

}
