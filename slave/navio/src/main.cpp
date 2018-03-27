#include <memory>
#include <iostream>
#include <exception>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include "sub.h"
#include "ports.h"

class XNetRecv {
private:
	Sub::Sub& sub;
	boost::array<char, 1024> recv_buf;
	boost::asio::io_service io_serv;
	boost::asio::ip::udp::socket sock{ io_serv };
	boost::asio::ip::udp::endpoint endp;

	void async_bind() {
		auto recv_bind = boost::bind(
			&XNetRecv::recv,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred);

		sock.async_receive_from(
			boost::asio::buffer(recv_buf),
			endp,
			recv_bind);
	}

public:
	XNetRecv(Sub::Sub& s) : sub(s) {
		sock.open(boost::asio::ip::udp::v4());
		sock.bind(boost::asio::ip::udp::endpoint(
			boost::asio::ip::address::from_string("10.42.0.58"),
			512));

		async_bind();
	}

	~XNetRecv() {
		sock.close();
	}

	void poll() {
		io_serv.poll();
	}

	void recv(const boost::system::error_code& error, size_t bytes) {
		if (error) {
			throw std::runtime_error("UDP error");
		}

		auto str = std::string(recv_buf.begin(), recv_buf.begin() + bytes);
		str = str.substr(1, str.length() - 2);

		std::vector<std::string> comps;
		boost::split(comps, str, boost::is_any_of(","));

		auto cvt = ::atof(comps[3].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("FTL"), cvt);
		}

		cvt = ::atof(comps[4].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("FBL"), cvt);
		}

		cvt = ::atof(comps[5].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("FTR"), cvt);
		}

		cvt = ::atof(comps[6].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("FBR"), cvt);
		}

		cvt = ::atof(comps[7].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("RTL"), cvt);
		}

		cvt = ::atof(comps[8].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("RBL"), cvt);
		}

		cvt = ::atof(comps[9].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("RTR"), cvt);
		}

		cvt = ::atof(comps[10].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports.at("RBR"), cvt);
		}

		async_bind();
	}
};

int main() {
	Sub::Sub& s = Sub::Sub::instance();
	XNetRecv net(s);

	while (true) {
		net.poll();
		s.update();
	}

	return 0;
}
