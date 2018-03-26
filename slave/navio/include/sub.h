#pragma once

#include <array>
#include <memory>
#include <iostream>
#include <exception>

#include "Navio2/PWM.h"
#include "Navio2/RCOutput_Navio2.h"
#include "Common/Util.h"

#define SERVO_STOP 1500
#define SERVO_MAG 600

/*
#define FLT_PORT 13;
#define fbl -1;
#define ftr -1;
#define fbr -1;

#define rtl -1;
#define rbl -1;
#define rtr -1;
#define rbr -1;
*/

class Sub {
private:
	enum VALUES {
		FTL, FBL, FRT, FBR,
		RTL, RBL, RTR, RBR
	};

	const std::array<int, 8> PORTS {{
		13, -1, -1, -1,
		-1, -1, -1, -1
	}};

	std::unique_ptr<RCOutput> pwm;

	Sub() {
		if (get_navio_version() != NAVIO2) {
			throw std::runtime_error("wrong navio");
		}

		if (check_apm()) {
			throw std::runtime_error("check_apm() test failed");

		}

		if  (getuid()) {
			throw std::runtime_error("not root");
		}

		pwm = std::unique_ptr<RCOutput>{ new RCOutput_Navio2() };

		for (auto p : PORTS) {
			if (!(pwm->initialize(p))) {
			}
		}
	}

	unsigned int get_servo_range(double mag) {
		return SERVO_STOP + mag * SERVO_MAG;
	}

public:
	static Sub& instance();
	Sub(const Sub&) = delete;
	void operator=(const Sub&) = delete;

	double ftl = 0;
	double fbl = 0;
	double ftr = 0;
	double fbr = 0;

	double rtl = 0;
	double rbl = 0;
	double rtr = 0;
	double rbr = 0;

	void update() {
		
	}
};
