#pragma once

#include <iostream>

struct R3 {
	union {
		struct {
			double x;
			double y;
			double z;
		};
		struct {
			double pitch;
			double yaw;
			double roll;
		};
		struct { double v[3]; };
	};
	
	R3();
	R3(const R3& copy);
	R3(const R3&& move);
	
	R3& operator= (R3 const& rhs);
	R3& operator= (R3&& rhs);

	R3 operator- () const;
	R3 operator+ () const;

	R3& operator+= (R3 const& rhs);
	R3& operator-= (R3 const& rhs);
	R3& operator*= (R3 const& rhs);
	R3& operator/= (R3 const& rhs);
	R3& operator%= (R3 const& rhs);

	enum class MEMBERS { X = 0, Y = 1, Z = 2 };
	double& operator[](MEMBERS const& index);
	const double& operator[](MEMBERS const& index) const;
};

bool operator== (R3 const& lhs, R3 const& rhs);
bool operator!= (R3 const& lhs, R3 const& rhs);
bool operator== (R3 const& lhs, double const& rhs);
bool operator!= (R3 const& lhs, double const& rhs);
bool operator== (double const& lhs, R3 const& rhs);
bool operator!= (double const& lhs, R3 const& rhs);

R3 operator+ (R3 const& lhs, R3 const& rhs);
R3 operator- (R3 const& lhs, R3 const& rhs);
R3 operator* (R3 const& lhs, R3 const& rhs);
R3 operator/ (R3 const& lhs, R3 const& rhs);
R3 operator% (R3 const& lhs, R3 const& rhs);
R3 operator+ (R3 const& lhs, double const& rhs);
R3 operator- (R3 const& lhs, double const& rhs);
R3 operator* (R3 const& lhs, double const& rhs);
R3 operator/ (R3 const& lhs, double const& rhs);
R3 operator% (R3 const& lhs, double const& rhs);
R3 operator+ (double const& lhs, R3 const& rhs);
R3 operator- (double const& lhs, R3 const& rhs);
R3 operator* (double const& lhs, R3 const& rhs);
R3 operator/ (double const& lhs, R3 const& rhs);
R3 operator% (double const& lhs, R3 const& rhs);

std::ostream& operator<< (std::ostream& os, R3 const& x);

struct R8 {
	union {
		struct {
			double ftl;
			double fbl;
			double ftr;
			double fbr;

			double rtl;
			double rbl;
			double rtr;
			double rbr;
		};
		struct { double v[8]; };
	};
	
	R8();
	R8(const R8& copy);
	R8(const R8&& move);

	R8& operator= (R8 const& rhs);
	R8& operator= (R8&& rhs);

	R8 operator- () const;
	R8 operator+ () const;

	R8& operator+= (R8 const& rhs);
	R8& operator-= (R8 const& rhs);
	R8& operator*= (R8 const& rhs);
	R8& operator/= (R8 const& rhs);
	R8& operator%= (R8 const& rhs);

	enum class MEMBERS { FTL = 0, FBL = 1, FTR = 2, FBR = 3, RTL = 4, RBL = 5, RTR = 6, RBR = 7 };
	double& operator[](MEMBERS const& index);
	const double& operator[](MEMBERS const& index) const;
	double& operator[](unsigned int const& index);
	const double& operator[](unsigned int const& index) const;
};

bool operator== (R8 const& lhs, R8 const& rhs);
bool operator!= (R8 const& lhs, R8 const& rhs);
bool operator== (R8 const& lhs, double const& rhs);
bool operator!= (R8 const& lhs, double const& rhs);
bool operator== (double const& lhs, R8 const& rhs);
bool operator!= (double const& lhs, R8 const& rhs);

R8 operator+ (R8 const& lhs, R8 const& rhs);
R8 operator- (R8 const& lhs, R8 const& rhs);
R8 operator* (R8 const& lhs, R8 const& rhs);
R8 operator/ (R8 const& lhs, R8 const& rhs);
R8 operator% (R8 const& lhs, R8 const& rhs);
R8 operator+ (R8 const& lhs, double const& rhs);
R8 operator- (R8 const& lhs, double const& rhs);
R8 operator* (R8 const& lhs, double const& rhs);
R8 operator/ (R8 const& lhs, double const& rhs);
R8 operator% (R8 const& lhs, double const& rhs);
R8 operator+ (double const& lhs, R8 const& rhs);
R8 operator- (double const& lhs, R8 const& rhs);
R8 operator* (double const& lhs, R8 const& rhs);
R8 operator/ (double const& lhs, R8 const& rhs);
R8 operator% (double const& lhs, R8 const& rhs);

std::ostream& operator<< (std::ostream& os, R8 const& x);
