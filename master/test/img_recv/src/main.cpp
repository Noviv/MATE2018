#include <iostream>

#include "common/xcvserialize.hpp"
#include "common/xnet.hpp"

int main() {
    cv::Mat frame;

    auto cb = [&frame](const std::string& str) {
        load(frame, str.c_str());
        imwrite("test.jpg", frame);
    };

    XNetRecv net("10.42.0.1", 513, cb);

    namedWindow("img_recv", cv::WINDOW_AUTOSIZE);

    bool running = true;
    while (running) {
        net.poll();
        if (!frame.empty()) {
            imshow("img_recv", frame);
        }
        if (cv::waitKey(30) >= 0) {
            std::cout << "fuck u" << std::endl;
            running = false;
        }
    }
}
