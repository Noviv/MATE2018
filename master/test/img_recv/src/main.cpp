#include <iostream>

#include "common/xcvserialize.hpp"
#include "common/xnet.hpp"

int main() {
    cv::Mat frame;

    auto cb = [&frame](const std::string& str) { load(frame, str.c_str()); };

    XNetRecv net("10.42.0.1", 513, cb);

    while (1) {
        net.poll();
		if (!frame.empty()) {
        	imshow("img_recv", frame);
		}
    }
}
