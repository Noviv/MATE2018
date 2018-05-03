#ifndef XNETSERV_HPP
#define XNETSERV_HPP

#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>

#include <exception>

class XNetMaster {
private:
    const std::string& ip;

    // serv variables
    const int& sPort;
    int lSokt;  // listen socket
    int sSokt;  // serv socket

    struct sockaddr_in sAddr;
    struct sockaddr_in lAddr;

    // recv variables
    const int& rPort;
    int rSokt;  // recv socket

    struct sockaddr_in serverAddr;

public:
    XNetMaster(const std::string& ip = "127.0.0.1",
               const int& sPort = 512,
               const int& rPort = 513)
        : ip(ip), sPort(sPort), rPort(rPort) {
        socklen_t addrLen = sizeof(struct sockaddr_in);

        // init serv
        std::cout << "XNetMaster init serv" << std::endl;

        lSokt = socket(AF_INET, SOCK_STREAM, 0);
        if (lSokt < 0) {
            throw std::runtime_error("XNetMaster lSokt == -1");
        }

        lAddr.sin_family = AF_INET;
        lAddr.sin_addr.s_addr = INADDR_ANY;
        lAddr.sin_port = htons(sPort);

        if (bind(lSokt, (struct sockaddr*)&lAddr, sizeof(lAddr)) < 0) {
            throw std::runtime_error("XNetMaster bind() failed");
        }

        listen(lSokt, 3);

        std::cout << "XNetMaster waiting for connection" << std::endl;

        sSokt = accept(lSokt, (struct sockaddr*)&sAddr, &addrLen);
        if (sSokt < 0) {
            throw std::runtime_error("XNetMaster rSokt < 0");
        }

        std::cout << "XNetMaster connection accepted" << std::endl;

        // init recv
        std::cout << "XNetMaster init recv" << std::endl;

        rSokt = socket(PF_INET, SOCK_STREAM, 0);
        if (rSokt < 0) {
            throw std::runtime_error("XNetMaster connect() failed");
        }

        serverAddr.sin_family = PF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        serverAddr.sin_port = htons(rPort);

        std::cout << "XNetMaster connecting" << std::endl;
        if (connect(rSokt, (sockaddr*)&serverAddr, addrLen) < 0) {
            throw std::runtime_error("XNetMaster connect() failed");
        }

        std::cout << "XNetMaster connected" << std::endl;
    }

    ~XNetMaster() {
        close(sSokt);
        close(rSokt);
        close(lSokt);
    }
};

#endif
