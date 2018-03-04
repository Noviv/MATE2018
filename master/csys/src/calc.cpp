#include "vec.h"
#include "calc.h"

#include <cmath>
#include <iostream>

static double maxComp(const R8& mult) {
    const double* data = (const double*) &mult;
    double max = 0; // something definitely less than the absolute value
    for (int i = 0; i < 8; ++i) {
        if (std::abs(data[i]) > max) {
            max = data[i];
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
#define ONLY_TRANSLATION 1
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

    std::cout << ret << std::endl;

	return ret;
#endif
#undef ONLY_TRANSLATION

#define BOTH 0
#if BOTH    
    // X -> left, right
    R8 x {
        1.0, 1.0,
        -1.0, -1.0,
        1.0, 1.0,
        -1.0, -1.0
    } * position.x;
    // Y -> top, bottom
    R8 y {
        1.0, -1.0,
        1.0, -1.0,
        1.0, -1.0,
        1.0, -1.0
    } * position.y;
    // Z -> front, back
    R8 z {
        -1.0, -1.0,
        -1.0, -1.0,
        1.0, 1.0,
        1.0, 1.0
    } * position.z;
    // pitch -> top front / bottom back - bottom front / top back
    R8 pitch {
        1.0, -1.0,
        1.0, -1.0,
        -1.0, 1.0,
        -1.0, 1.0
    } * rotation.x;
    // roll -> top left / bottom right - bottom left / top right
    R8 roll {
        1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        -1.0, 1.0
    } * rotation.z;
    // yaw -> front left / back right - front right / back left
    R8 yaw {
        1.0, 1.0,
        -1.0, -1.0,
        -1.0, -1.0,
        1.0, 1.0
    } * rotation.y;
    
    return (x + y + z + pitch + roll + yaw) / maxComp(totality);
#endif
#undef BOTH
}
