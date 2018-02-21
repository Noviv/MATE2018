#pragma once

#include <string>
#include <boost/asio.hpp>

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
	void send_v(double x, double y, double z, int sens);
};