#pragma once

typedef struct {
	double x;
	double y;
	double z;
} R3;

typedef struct {
	double ftl;
	double fbl;
	double ftr;
	double fbr;

	double rtl;
	double rbl;
	double rtr;
	double rbr;
} R8;

R8 calc(R3, R3);
