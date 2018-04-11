#ifndef CALC_H
#define CALC_H

#include <cmath>
#include <iostream>

#include "common/xmath.h"

R<8> calc(R<3> position, R<3> rotation) {
	// X -> left - right
	R<8> x {
		1.0, 1.0,
		-1.0, -1.0,
		1.0, 1.0,
		-1.0, -1.0
	};
	x *= position[0];
	// Y -> top - bottom
	R<8> y {
		1.0, -1.0,
		1.0, -1.0,
		1.0, -1.0,
		1.0, -1.0
	};
	y *= position[1];
	// Z -> front - rear
	R<8> z {
		1.0, 1.0,
		1.0, 1.0,
		-1.0, -1.0,
		-1.0, -1.0
	};
	z *= position[2];
	// pitch -> front top / rear bottom - front bottom / rear top
	R<8> pitch {
		1.0, -1.0,
		1.0, -1.0,
		-1.0, 1.0,
		-1.0, 1.0
	};
	pitch *= rotation[0];
	// roll -> top left / bottom right - bottom left / top right
	R<8> roll {
		1.0, -1.0,
		-1.0, 1.0,
		1.0, -1.0,
		-1.0, 1.0
	};
	roll *= rotation[1];
	// yaw -> front left / rear right - front right / rear left
	R<8> yaw {
		1.0, 1.0,
		-1.0, -1.0,
		-1.0, -1.0,
		1.0, 1.0
	};
	yaw *= rotation[2];
	auto early_trans_sum = x + y + z;
    auto early_rot_sum = pitch + roll + yaw;
    return (early_trans_sum + early_rot_sum);
}

#endif
