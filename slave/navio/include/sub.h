#pragma once

#include <array>
#include <memory>
#include <iostream>
#include <exception>
#include <unordered_map>

#include "Navio2/PWM.h"
#include "Navio2/RCOutput_Navio2.h"
#include "Common/Util.h"

#define SERVO_STOP 1500
#define SERVO_MAG 600
#define SERVO_FREQ 50

namespace Sub {

static int FTL = 0; // front top left
static int FBL = 1; // front bottom left
static int FTR = 2; // front top right
static int FBR = 3;
static int RTL = 4; // rear top left
static int RBL = 5;
static int RTR = 6;
static int RBR = 7;

class Thruster {
private:
	std::unique_ptr<RCOutput>& pwm;
	double thrust;
	int port;

	static constexpr unsigned int get_servo_range(double mag) {
		return SERVO_STOP + mag * SERVO_MAG;
	}

public:
	Thruster(int p, std::unique_ptr<RCOutput>& pwm) : port(p), pwm(pwm) {
		if (!(pwm->initialize(p))) {
			throw std::runtime_error("failed init: " + p);
		}
		pwm->set_frequency(p, SERVO_FREQ);
		if (!(pwm->enable(p))) {
			throw std::runtime_error("failed enable: " + p);
		}
	}

	void set_thrust(double t) {
		thrust = t;
	}

	void update() {
		pwm->set_duty_cycle(port, get_servo_range(thrust));
	}
};

class Sub {
private:
	std::unordered_map<int, Thruster> thrusters;

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

		for (int i = 0; i < 8; ++i) {
			thrusters.insert({ i, Thruster(i, pwm) });
		}
	}

public:
	static Sub& instance() {
		static Sub instance;
		return instance;
	}

	Sub(const Sub&) = delete;
	void operator=(const Sub&) = delete;

	void set_thrust(int p, double t) {
		thrusters.at(p).set_thrust(t);
	}

	void update() {
		for (auto& t : thrusters) {
			t.second.update();
		}
	}
};

}
