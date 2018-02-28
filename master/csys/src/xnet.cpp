#include "xnet.h"

#include <sstream>

XNet::XNet() {
	sock = new boost::asio::ip::udp::socket(io_serv);
	endp = new boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::broadcast(), 512);

	sock->open(boost::asio::ip::udp::v4(), error);
	if (!error) {
		sock->set_option(boost::asio::ip::udp::socket::reuse_address(true));
		sock->set_option(boost::asio::socket_base::broadcast(true));
	}
}

void XNet::send(std::string data) {
	sock->send_to(boost::asio::buffer(data, data.size()), *endp);
}


void XNet::send_v(double x, double y, double z, int sens) {
	std::ostringstream strstream;
	strstream << "[";
	strstream << x / sens;
	strstream << ",";
	strstream << y / sens;
	strstream << ",";
	strstream << z / sens;
	strstream << "]";

	send(strstream.str());
}

XNet::~XNet() {
	sock->close();
	free(sock);
	free(endp);
}
