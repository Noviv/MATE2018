#include "net.h"

#include <sstream>

XNet::XNet() {
	sock = new boost::asio::ip::udp::socket(io_serv);
	endp = new boost::asio::ip::udp::endpoint(
		boost::asio::ip::address::from_string("127.0.0.1"),
		512);

	sock->open(boost::asio::ip::udp::v4());
}

void XNet::send(std::string data) {
	sock->send_to(boost::asio::buffer(data, data.size()), *endp);
}


void XNet::send_v(R3 d, R8 thrusts, int sens) {
	std::ostringstream strstream;
	strstream << "[";
	strstream << d.x / sens << ",";
	strstream << d.y / sens << ",";
	strstream << d.z / sens << ",";
	strstream << thrusts.ftl / sens << ",";
	strstream << thrusts.fbl / sens << ",";
	strstream << thrusts.ftr / sens << ",";
	strstream << thrusts.fbr / sens << ",";
	strstream << thrusts.rtl / sens << ",";
	strstream << thrusts.rbl / sens << ",";
	strstream << thrusts.rtr / sens << ",";
	strstream << thrusts.rbr / sens;
	strstream << "]";

	send(strstream.str());
}

XNet::~XNet() {
	sock->close();
	free(sock);
	free(endp);
}
