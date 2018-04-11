#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include "common/xnet.h"
#include "sub.h"

int main() {
	auto& sub = Sub::instance();

	auto func = [&sub](std::string str) {
		if (str[0] != '8') {
			if (str[0] == '0') {
				sub.disarm();
			}
			if (str[0] == '1') {
				sub.arm();
			}
			// some other command
			return;
		}

		str = str.substr(2, str.size() - 3);

		std::vector<std::string> comps;
		boost::split(comps, str, boost::is_any_of(","));

		auto cvt = ::atof(comps[3].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("FTL"), cvt);
		}

		cvt = ::atof(comps[4].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("FBL"), cvt);
		}

		cvt = ::atof(comps[5].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("FTR"), cvt);
		}

		cvt = ::atof(comps[6].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("FBR"), cvt);
		}

		cvt = ::atof(comps[7].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("RTL"), cvt);
		}

		cvt = ::atof(comps[8].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("RBL"), cvt);
		}

		cvt = ::atof(comps[9].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("RTR"), cvt);
		}

		cvt = ::atof(comps[10].c_str());
		if (cvt == cvt) {
			sub.set_thrust(ports_at("RBR"), cvt);
		}
	};

	XNetRecv<1024> net("10.42.0.58", func);

	while (true) {
		net.poll();
		sub.update();
	}

	return 0;
}
