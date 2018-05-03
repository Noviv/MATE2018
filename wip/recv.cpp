#include <arpa/inet.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

#include "opencv2/opencv.hpp"

int main() {
    int sokt;
    const char* ip = "10.42.0.58";
    int port = 4123;

    struct sockaddr_in serverAddr;
    socklen_t addrLen = sizeof(struct sockaddr_in);

    if ((sokt = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "socket() failed" << std::endl;
        return 1;
    }

    serverAddr.sin_family = PF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(port);

    if (connect(sokt, (sockaddr*)&serverAddr, addrLen) < 0) {
        std::cerr << "connect() failed" << std::endl;
        return 1;
    }

    cv::Mat img(480, 640, CV_8UC1);
    int sz = img.total() * img.elemSize();
    uchar* iptr = img.data;
    int bytes = 0;

    if (!img.isContinuous()) {
        img = img.clone();
    }

    std::cout << "sz : " << sz << std::endl;

    cv::namedWindow("recv", 1);

    while (1) {
        if ((bytes = recv(sokt, iptr, sz, MSG_WAITALL)) == -1) {
            std::cerr << "recv failed" << std::endl;
            return 1;
        }

        cv::imshow("recv", img);

        int wk = cv::waitKey(10);
        if (wk >= 0 && wk != 255) {
            break;
        }
    }

    close(sokt);
}
