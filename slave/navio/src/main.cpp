#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include "common/xnet.hpp"
#include "sub.hpp"

int main() {
    auto& sub = Sub::instance();

    auto func = [&sub](const std::string& _str) {
        if (_str[0] != '8') {
            if (_str[0] == '0') {
                sub.disarm();
            }
            if (_str[0] == '1') {
                sub.arm();
            }
            // some other command
            return;
        }

        auto str = _str.substr(2, _str.size() - 3);

        std::vector<std::string> comps;
        boost::split(comps, str, boost::is_any_of(","));

        auto cvt = ::atof(comps[3].c_str());
        if (cvt == cvt) {
            sub.set_thrust(FTL, cvt);
        }

        cvt = ::atof(comps[4].c_str());
        if (cvt == cvt) {
            sub.set_thrust(FBL, cvt);
        }

        cvt = ::atof(comps[5].c_str());
        if (cvt == cvt) {
            sub.set_thrust(FTR, cvt);
        }

        cvt = ::atof(comps[6].c_str());
        if (cvt == cvt) {
            sub.set_thrust(FBR, cvt);
        }

        cvt = ::atof(comps[7].c_str());
        if (cvt == cvt) {
            sub.set_thrust(RTL, cvt);
        }

        cvt = ::atof(comps[8].c_str());
        if (cvt == cvt) {
            sub.set_thrust(RBL, cvt);
        }

        cvt = ::atof(comps[9].c_str());
        if (cvt == cvt) {
            sub.set_thrust(RTR, cvt);
        }

        cvt = ::atof(comps[10].c_str());
        if (cvt == cvt) {
            sub.set_thrust(RBR, cvt);
        }
    };

    XNetRecv net("10.42.0.234", 512, func);

    while (true) {
        net.poll();
        sub.update();
    }

    return 0;
}
