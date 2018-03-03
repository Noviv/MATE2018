#pragma once

#include <string>
#include <boost/asio.hpp>

#include "calc.h"

class XNet {
private:
	boost::system::error_code error;
	boost::asio::io_service io_serv;
	boost::asio::ip::udp::socket* sock;
	boost::asio::ip::udp::endpoint* endp;
public:
	XNet();
	~XNet();
	void send(std::string);
	void send_v(R3, R8, int);
};
