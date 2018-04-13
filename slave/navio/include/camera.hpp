#ifndef CAMERA_H
#define CAMERA_H

#include "common/xcvserialize.hpp"
#include "common/xnet.hpp"

class NetCamera {
  private:
    cv::VideoCapture cap;
    cv::Mat frame;

    XNet net;

  public:
    NetCamera() : cap(0), net("10.42.0.1", 513) {}

    void update() {
        cap >> frame;

        cv::resize(frame, frame, cv::Size(10, 10));

        auto data = save(frame);

        net.send(data);
    }
};

#endif
