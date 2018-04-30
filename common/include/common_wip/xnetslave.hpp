#ifndef XNETSLAVE_HPP
#define XNETSLAVE_HPP

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

class XNetSlave {
   private:
    const std::string& ip;

    // recv variables
    const int& rPort;
    int rSokt;  // recv socket

    // serv variables
    const int& sPort;
    int lSokt;  // listen socket
    int sSokt;  // serv socket

    struct sockaddr_in lAddr;
    struct sockaddr_in sAddr;

    struct sockaddr_in serverAddr;

   public:
    XNetSlave(const std::string& ip = "127.0.0.1",
              const int& rPort = 512,
              const int& sPort = 513)
        : ip(ip), rPort(rPort), sPort(sPort) {
        socklen_t addrLen = sizeof(struct sockaddr_in);

		// init recv
		std::cout << "XNetSlave init recv" << std::endl;

        rSokt = socket(PF_INET, SOCK_STREAM, 0);
        if (rSokt < 0) {
            throw std::runtime_error("XNetSlave connect() failed");
        }

        serverAddr.sin_family = PF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        serverAddr.sin_port = htons(rPort);

		std::cout << "XNetSlave connecting" << std::endl;
        if (connect(rSokt, (sockaddr*)&serverAddr, addrLen) < 0) {
            throw std::runtime_error("XNetSlave connect() failed");
        }

		std::cout << "XNetSlave connected" << std::endl;

		// init serv
		std::cout << "XNetSlave init serv" << std::endl;

		lSokt = socket(AF_INET, SOCK_STREAM, 0);
		if (lSokt < 0) {
			throw std::runtime_error("XNetSlave lSokt == -1");
		}

        lAddr.sin_family = AF_INET;
        lAddr.sin_addr.s_addr = INADDR_ANY;
        lAddr.sin_port = htons(sPort);

        if (bind(lSokt, (struct sockaddr*)&lAddr, sizeof(lAddr)) < 0) {
            throw std::runtime_error("XNetSlave bind() failed");
        }

        listen(lSokt, 3);

        std::cout << "XNetSlave waiting for connection" << std::endl;

        sSokt = accept(lSokt, (struct sockaddr*)&sAddr, &addrLen);
        if (sSokt < 0) {
            throw std::runtime_error("XNetSlave rSokt < 0");
        }

        std::cout << "XNetSlave connection accepted" << std::endl;
    }

    ~XNetSlave() {
        close(rSokt);
        close(lSokt);
		close(sSokt);
    }
};

#endif
