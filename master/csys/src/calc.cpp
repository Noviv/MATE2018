#include "vec.h"
#include "calc.h"

#include <cmath>
#include <iostream>

static double maxComp(const R8& vec) {
	double max = 0; // something definitely less than the absolute value
	for (int i = 0; i < 8; ++i) {
		if (std::abs(vec[i]) > max) {
			max = std::abs(vec[i]);
		}
	}
	return max == 0 ? 1 : max;
}

// TODO: check if input is correctly formatted
R8 calc(R3 position, R3 rotation) {
	R8 ret {
		0, 0, 0, 0,
		0, 0, 0, 0
	};

#define ONLY_TRANSLATION 0
#if ONLY_TRANSLATION
	ret.ftl = 0.577350269 * position.x
		+ 0.577350269 * position.y
		+ 0.577350269 * position.z;

	ret.fbl = 0.577350269 * position.x
		- 0.577350269 * position.y
		+ 0.577350269 * position.z;

	ret.ftr = -0.577350269 * position.x
		+ 0.577350269 * position.y
		+ 0.577350269 * position.z;

	ret.fbr = -0.577350269 * position.x
		- 0.577350269 * position.y
		+ 0.577350269 * position.z;

	ret.rtl = 0.577350269 * position.x
		+ 0.577350269 * position.y
		- 0.577350269 * position.z;

	ret.rbl = 0.577350269 * position.x
		- 0.577350269 * position.y
		- 0.577350269 * position.z;

	ret.rtr = -0.577350269 * position.x
		+ 0.577350269 * position.y
		- 0.577350269 * position.z;

	ret.rbr = -0.577350269 * position.x
		- 0.577350269 * position.y
		- 0.577350269 * position.z;

	return ret;
#else
	// X -> left - right
	R8 x {
		1.0, 1.0,
		-1.0, -1.0,
		1.0, 1.0,
		-1.0, -1.0
	};
	x *= position.x;
	// Y -> top - bottom
	R8 y {
		1.0, -1.0,
		1.0, -1.0,
		1.0, -1.0,
		1.0, -1.0
	};
	y *= position.y;
	// Z -> front - rear
	R8 z {
		1.0, 1.0,
		1.0, 1.0,
		-1.0, -1.0,
		-1.0, -1.0
	};
	z *= position.z;
	// pitch -> front top / rear bottom - front bottom / rear top
	R8 pitch {
		1.0, -1.0,
		1.0, -1.0,
		-1.0, 1.0,
		-1.0, 1.0
	};
	pitch *= rotation.pitch;
	// roll -> top left / bottom right - bottom left / top right
	R8 roll {
		1.0, -1.0,
		-1.0, 1.0,
		1.0, -1.0,
		-1.0, 1.0
	};
	roll *= rotation.roll;
	// yaw -> front left / rear right - front right / rear left
	R8 yaw {
		1.0, 1.0,
		-1.0, -1.0,
		-1.0, -1.0,
		1.0, 1.0
	};
	yaw *= rotation.yaw;
	auto early_trans_sum = x + y + z;
    auto early_rot_sum = pitch + roll + yaw;
    return (early_trans_sum + early_rot_sum) / 6;
}
