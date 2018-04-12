#include <iostream>

#include "common/xnet.hpp"
#include "common/xcvserialize.hpp"

int main() {
	cv::Mat frame;

	auto cb = [&frame](const std::string& str) {
		load(frame, str.c_str());
	};

	XNetRecv net("127.0.0.1", 512, cb);

	while (1) {
		net.poll();
		imshow("img_recv", frame);
	}
}
