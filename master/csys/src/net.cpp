#include "net.h"

#include <sstream>

XNet::XNet() : sock(io_serv), endp(BAI::address::from_string("10.42.0.58"), 512) {
	sock.open(BAI::udp::v4());
}

XNet::~XNet() {
	sock.close();
}

void XNet::send(std::string data) {
	sock.send_to(boost::asio::buffer(data, data.size()), endp);
}


void XNet::send_v(R3 d, R8 thrusts) {
	std::ostringstream strstream;
	strstream << "[";
	strstream << d.x << ",";
	strstream << d.y << ",";
	strstream << d.z << ",";
	strstream << thrusts.ftl << ",";
	strstream << thrusts.fbl << ",";
	strstream << thrusts.ftr << ",";
	strstream << thrusts.fbr << ",";
	strstream << thrusts.rtl << ",";
	strstream << thrusts.rbl << ",";
	strstream << thrusts.rtr << ",";
	strstream << thrusts.rbr;
	strstream << "]";

	send(strstream.str());
}
