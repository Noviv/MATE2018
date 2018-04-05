#ifndef SUB_H
#define SUB_H

#include <array>
#include <memory>
#include <iostream>
#include <exception>
#include <algorithm>

#include "Navio2/PWM.h"
#include "Navio2/RCOutput_Navio2.h"
#include "Common/Util.h"

#include "ports.h"
#include "camera.h"

#define SERVO_STOP 1500
#define SERVO_MAG 600
#define SERVO_FREQ 50

class Thruster {
private:
	double thrust;
	int port;

	static constexpr unsigned int get_servo_range(double mag) {
		return SERVO_STOP + mag * SERVO_MAG;
	}

public:
	Thruster(int p, std::unique_ptr<RCOutput>& pwm) : port(p) {
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

	void update(std::unique_ptr<RCOutput>& pwm) {
		pwm->set_duty_cycle(port, get_servo_range(thrust));
	}
};

class Sub {
private:
	std::unordered_map<int, Thruster> thrusters;
	std::unique_ptr<RCOutput> pwm;

	NetCamera cam;

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

		for (auto& p : ports) {
			thrusters.insert({ p.second, Thruster(p.second, pwm) });
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
		if (p != -1) {
			thrusters.at(p).set_thrust(t);
		}
	}

	void update() {
		for (auto& t : thrusters) {
			t.second.update(pwm);
		}

		cam.update();
	}
};

#endif
