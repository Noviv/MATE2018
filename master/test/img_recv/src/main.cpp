#include <iostream>

#include "common/xcvserialize.hpp"
#include "common/xnet.hpp"

int main() {
    cv::Mat frame;

    auto cb = [&frame](const std::string& str) {
		std::cout << str << std::endl;
        load(frame, str.c_str());
    };

    XNetRecv net("10.42.0.1", 513, cb);

    namedWindow("img_recv", cv::WINDOW_AUTOSIZE);

    while (1) {
        net.poll();
        if (!frame.empty()) {
            imshow("img_recv", frame);
        }
		int wk = cv::waitKey(30);
        if (wk >= 0 && wk != 255) {
            std::cout << wk << std::endl;
			break;
        }
    }
}
