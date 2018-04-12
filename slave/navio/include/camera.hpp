#ifndef CAMERA_H
#define CAMERA_H

#include "common/xnet.hpp"
#include "common/xcvserialize.hpp"

class NetCamera {
private:
	cv::VideoCapture cap;
	cv::Mat frame;

	XNet net;

public:
	NetCamera() : cap(0), net("127.0.0.1", 512) {}

	void update() {
		cap >> frame;

		auto data = save(frame);

		net.send(data);
	}
};

#endif
