#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

#include "opencv2/opencv.hpp"

cv::VideoCapture cap(0);

void display(int* ptr) {
    int sokt = *ptr;

    cv::Mat img(480, 640, CV_8UC1);
    cv::Mat imgGray;
    if (!img.isContinuous()) {
        img = img.clone();
    }

    int sz = img.total() * img.elemSize();
    int bytes = 0;

    while (1) {
        cap >> img;

        cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

        if ((bytes = send(sokt, imgGray.data, sz, 0)) < 0) {
            perror("send() failed");
            break;
        }
    }
}

int main() {
    if (!cap.isOpened()) {
        std::cerr << "cap not opened" << std::endl;
        return 1;
    }

    int lSokt;
    int rSokt;
    int port = 4123;

    struct sockaddr_in lAddr;
    struct sockaddr_in rAddr;

    int addrLen = sizeof(struct sockaddr_in);

    lSokt = socket(AF_INET, SOCK_STREAM, 0);
    if (lSokt == -1) {
        std::cerr << "lSokt == -1" << std::endl;
    }
    lAddr.sin_family = AF_INET;
    lAddr.sin_addr.s_addr = INADDR_ANY;
    lAddr.sin_port = htons(port);

    if (bind(lSokt, (struct sockaddr*)&lAddr, sizeof(lAddr)) < 0) {
        perror("bind() failed");
        return 1;
    }

    listen(lSokt, 3);

    std::cout << "waiting for a connection" << std::endl;

    rSokt = accept(lSokt, (struct sockaddr*)&rAddr, (socklen_t*)&addrLen);

    if (rSokt < 0) {
        std::cerr << "rSokt < 0" << std::endl;
        return 1;
    }

    std::cout << "connection accepted" << std::endl;
    display(&rSokt);

    close(rSokt);
    close(lSokt);
}
