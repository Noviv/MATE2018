#include "calc.h"

#include <stdio.h>

// Could also overload operators
static R8 add(const R8& alph, const R8& beta) {
    return R8 {
        alph.ftl + beta.ftl,
        alph.fbl + beta.fbl,
        alph.ftr + beta.ftr,
        alph.fbr + beta.fbr,
        alph.rtl + beta.rtl,
        alph.rbl + beta.rbl,
        alph.rtr + beta.rtr,
        alph.rbr + beta.rbr
    };
}
static void mult(R8& mult, double scale) {
    mult.ftl *= scale;
    mult.fbl *= scale;
    mult.ftr *= scale;
    mult.fbr *= scale;
    mult.rtl *= scale;
    mult.rbl *= scale;
    mult.rtr *= scale;
    mult.rbr *= scale;
}
static double maxComp(const R8& mult) {
    const double* data = (const double*) &mult;
    double max = -1; // should use the limits lib
    for (int i = 0; i < 8; ++i) {
        if (data[i] > max) {
            max = data[i];
        }
    }
    return max;
}

// TODO: check if input is correctly formatted
R8 calc(R3 position, R3 rotation) {
	R8 ret {
		0, 0, 0, 0,
		0, 0, 0, 0
	};

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

	printf("%f\n", ret.rbr);

	return ret;
    // X -> left, right
    R8 x {
        1.0, 1.0,
        -1.0, -1.0,
        1.0, 1.0,
        -1.0, -1.0
    };
    mult(x, position.x);
    // Y -> top, bottom
    R8 y {
        1.0, -1.0,
        1.0, -1.0,
        1.0, -1.0,
        1.0, -1.0
    };
    mult(y, position.y);
    // Z -> front, back
    R8 z {
        -1.0, -1.0,
        -1.0, -1.0,
        1.0, 1.0,
        1.0, 1.0
    };
    mult(z, position.z);
    // pitch -> top front / bottom back - bottom front / top back
    R8 pitch {
        1.0, -1.0,
        1.0, -1.0,
        -1.0, 1.0,
        -1.0, 1.0
    };
    mult(pitch, rotation.x);
    // roll -> top left / bottom right - bottom left / top right
    R8 roll {
        1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        -1.0, 1.0
    };
    mult(roll, rotation.z);
    // yaw -> front left / back right - front right / back left
    R8 yaw {
        1.0, 1.0,
        -1.0, -1.0,
        -1.0, -1.0,
        1.0, 1.0
    };
    mult(yaw, rotation.y);
    
    auto totality = add(add(add(add(add(x, y), z), pitch), roll), yaw);
    
    mult(totality, 1.0 / maxComp(totality));
    
    return totality;
}
