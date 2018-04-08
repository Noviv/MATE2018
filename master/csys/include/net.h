#ifndef NET_H
#define NET_H

#include <string>
#include <sstream>
#include <boost/asio.hpp>

#include "vec.h"

class XNet {
private:
	boost::system::error_code error;
	boost::asio::io_service io_serv;
	boost::asio::ip::udp::socket sock;
	boost::asio::ip::udp::endpoint endp;

public:
	XNet() : sock(io_serv), endp(boost::asio::ip::address::from_string(""), 512) {
		sock.open(boost::asio::ip::udp::v4());
	};

	~XNet() {
		sock.close();
	}

	void send(std::string data) {
		sock.send_to(boost::asio::buffer(data, data.size()), endp);
	}

	void send_v(R3 d, R8 thrusts) {
		std::ostringstream strstream;
		strstream << "8[";
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
};

#endif
