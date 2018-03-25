#include <memory>
#include <iostream>
#include <unistd.h>

#include "Navio2/PWM.h"
#include "Navio+/RCOutput_Navio.h"
#include "Navio2/RCOutput_Navio2.h"
#include "Common/Util.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#define SERVO_STOP 1500
#define SERVO_MAG 600

#define PWM_OUTPUT 0

double ftl = 0;

class XNetRecv {
private:
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
	XNetRecv() {
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
			std::cout << "UDP error" << std::endl;
			return;
		}

		auto str = std::string(recv_buf.begin(), recv_buf.begin() + bytes);
		str = str.substr(1, str.length() - 2);

		std::vector<std::string> comps;
		boost::split(comps, str, boost::is_any_of(","));

		auto cvt = ::atof(comps[0].c_str());
		if (cvt == cvt) {
			//d_x
		}

		cvt = ::atof(comps[3].c_str());
		if (cvt == cvt) {
			ftl = cvt;
		}

		async_bind();
	}
};

constexpr unsigned int get_servo_range(double mag) {
	return SERVO_STOP + mag * SERVO_MAG;
}

inline std::unique_ptr<PCA9685> get_rcout() {
	return std::unique_ptr <PCA9685> { new PCA9685() };
}

int main() {
	if (get_navio_version() != NAVIO2) {
		std::cout << "wtf using wrong navio" << std::endl;
		return 1;
	}

	if (check_apm()) {
		std::cout << "check_apm() test failed" << std::endl;
		return 1;
	}

	if  (getuid()) {
		std::cout << "not root" << std::endl;
		return 1;
	}

	auto pwm = get_rcout();

/*
	if (!(pwm->initialize(PWM_OUTPUT))) {
		std::cout << "could not init pwm" << std::endl;
		return 1;
	}

	pwm->set_frequency(PWM_OUTPUT, 50);

	if (!(pwm->enable(PWM_OUTPUT))) {
		std::cout << "could not enable" << std::endl;
		return 1;
	}
*/

	pwm->initialize();
	pwm->setFrequency(50);
	if (!(pwm->testConnection()) {
		
	}
	pwm->testConnection();

	XNetRecv net;

	while (true) {
		net.poll();
		pwm->setPWMuS(PWM_OUTPUT, get_servo_range(ftl));
		//pwm->set_duty_cycle(PWM_OUTPUT, get_servo_range(ftl));
		std::cout << get_servo_range(ftl) << std::endl;
	}

	return 0;
}
