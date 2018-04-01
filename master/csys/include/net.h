#pragma once

#include <string>
#include <boost/asio.hpp>

#include "vec.h"
#include "calc.h"

#define BAI boost::asio::ip

class XNet {
private:
	boost::system::error_code error;
	boost::asio::io_service io_serv;
	BAI::udp::socket sock;
	BAI::udp::endpoint endp;
public:
	XNet();
	~XNet();
	void send(std::string);
	void send_v(R3, R8);
};
