#include "vec.h"

#include <iostream>

R3 R3::operator- () const {
	return R3(*this) * -1;
}
R3 R3::operator+ () const {
	return *this;
}

R3& R3::operator+= (R3 const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] += rhs[i];
	return *this;
}
R3& R3::operator-= (R3 const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] -= rhs[i];
	return *this;
}
R3& R3::operator*= (R3 const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] *= rhs[i];
	return *this;
}
R3& R3::operator/= (R3 const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] /= rhs[i];
	return *this;
}

R3& R3::operator+= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] += rhs;
	return *this;
}
R3& R3::operator-= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] -= rhs;
	return *this;
}
R3& R3::operator*= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] *= rhs;
	return *this;
}
R3& R3::operator/= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] /= rhs;
	return *this;
}

double& R3::operator[](R3::MEMBERS const& index) {
	return v[(int) index];
}
const double& R3::operator[](R3::MEMBERS const& index) const {
	return v[(int) index];
}

double& R3::operator[](int const& index) {
	return (*this)[static_cast<R3::MEMBERS>(index)];
}
const double& R3::operator[](int const& index) const {
	return (*this)[static_cast<R3::MEMBERS>(index)];
}

bool operator== (R3 const& lhs, R3 const& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
bool operator!= (R3 const& lhs, R3 const& rhs) {
	return !(lhs == rhs);
}
bool operator== (R3 const& lhs, double const& rhs) {
	return lhs.x == rhs && lhs.y == rhs && lhs.z == rhs;
}
bool operator!= (R3 const& lhs, double const& rhs) {
	return !(lhs == rhs);
}
bool operator== (double const& lhs, R3 const& rhs) {
	return rhs == lhs;
}
bool operator!= (double const& lhs, R3 const& rhs) {
	return !(rhs == lhs);
}

R3 operator+ (R3 const& lhs, R3 const& rhs) {
	R3 tmp(lhs);
	tmp += rhs;
	return tmp;
}
R3 operator- (R3 const& lhs, R3 const& rhs) {
	R3 tmp(lhs);
	tmp -= rhs;
	return tmp;
}
R3 operator* (R3 const& lhs, R3 const& rhs) {
	R3 tmp(lhs);
	tmp *= rhs;
	return tmp;
}
R3 operator/ (R3 const& lhs, R3 const& rhs) {
	R3 tmp(lhs);
	tmp /= rhs;
	return tmp;
}
R3 operator+ (R3 const& lhs, double const& rhs) {
	R3 tmp(lhs);
	tmp += rhs;
	return tmp;
}
R3 operator- (R3 const& lhs, double const& rhs) {
	R3 tmp(lhs);
	tmp -= rhs;
	return tmp;
}
R3 operator* (R3 const& lhs, double const& rhs) {
	R3 tmp(lhs);
	tmp *= rhs;
	return tmp;
}
R3 operator/ (R3 const& lhs, double const& rhs) {
	R3 tmp(lhs);
	tmp /= rhs;
	return tmp;
}
R3 operator+ (double const& lhs, R3 const& rhs) {
	R3 tmp(rhs);
	tmp += lhs;
	return tmp;
}
R3 operator- (double const& lhs, R3 const& rhs) {
	R3 tmp(rhs);
	tmp -= lhs;
	return tmp;
}
R3 operator* (double const& lhs, R3 const& rhs) {
	R3 tmp(rhs);
	tmp *= lhs;
	return tmp;
}
R3 operator/ (double const& lhs, R3 const& rhs) {
	R3 tmp(rhs);
	tmp /= lhs;
	return tmp;
}

std::ostream& operator<< (std::ostream& os, R3 const& r3) {
	os << "R3 { x: " << r3.z << ", y: " << r3.y << ", z: " << r3.z << " }";
	return os;
}

// Redo the exact same thing for R8

R8 R8::operator- () const {
	return R8(*this) * -1;
}
R8 R8::operator+ () const {
	return *this;
}

R8& R8::operator+= (R8 const& rhs) {
	for (int i = 0; i < 8; i++) (*this)[i] += rhs[i];
	return *this;
}
R8& R8::operator-= (R8 const& rhs) {
	for (int i = 0; i < 8; i++) (*this)[i] -= rhs[i];
	return *this;
}
R8& R8::operator*= (R8 const& rhs) {
	for (int i = 0; i < 8; i++) (*this)[i] *= rhs[i];
	return *this;
}
R8& R8::operator/= (R8 const& rhs) {
	for (int i = 0; i < 8; i++) (*this)[i] /= rhs[i];
	return *this;
}

R8& R8::operator+= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] += rhs;
	return *this;
}
R8& R8::operator-= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] -= rhs;
	return *this;
}
R8& R8::operator*= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] *= rhs;
	return *this;
}
R8& R8::operator/= (double const& rhs) {
	for (int i = 0; i < 3; i++) (*this)[i] /= rhs;
	return *this;
}

double& R8::operator[](R8::MEMBERS const& index) {
	return v[(int) index];
}
const double& R8::operator[](R8::MEMBERS const& index) const {
	return v[(int) index];
}

double& R8::operator[](int const& index) {
	return (*this)[static_cast<R8::MEMBERS>(index)];
}
const double& R8::operator[](int const& index) const {
	return (*this)[static_cast<R8::MEMBERS>(index)];
}

bool operator== (R8 const& lhs, R8 const& rhs) {
	return lhs.ftl == rhs.ftl && lhs.fbl == rhs.fbl && lhs.ftr == rhs.ftr && lhs.fbr == rhs.fbr
		&& lhs.rtl == rhs.rtl && lhs.rbl == rhs.rbl && lhs.rtr == rhs.rtr && lhs.rbr == rhs.rbr;
}
bool operator!= (R8 const& lhs, R8 const& rhs) {
	return !(lhs == rhs);
}
bool operator== (R8 const& lhs, double const& rhs) {
	return lhs.ftl == rhs && lhs.fbl == rhs && lhs.ftr == rhs && lhs.fbr == rhs
		&& lhs.rtl == rhs && lhs.rbl == rhs && lhs.rtr == rhs && lhs.rbr == rhs;
}
bool operator!= (R8 const& lhs, double const& rhs) {
	return !(lhs == rhs);
}
bool operator== (double const& lhs, R8 const& rhs) {
	return rhs == lhs;
}
bool operator!= (double const& lhs, R8 const& rhs) {
	return !(rhs == lhs);
}

R8 operator+ (R8 const& lhs, R8 const& rhs) {
	R8 tmp(lhs);
	tmp += rhs;
	return tmp;
}
R8 operator- (R8 const& lhs, R8 const& rhs) {
	R8 tmp(lhs);
	tmp -= rhs;
	return tmp;
}
R8 operator* (R8 const& lhs, R8 const& rhs) {
	R8 tmp(lhs);
	tmp *= rhs;
	return tmp;
}
R8 operator/ (R8 const& lhs, R8 const& rhs) {
	R8 tmp(lhs);
	tmp /= rhs;
	return tmp;
}
R8 operator+ (R8 const& lhs, double const& rhs) {
	R8 tmp(lhs);
	tmp += rhs;
	return tmp;
}
R8 operator- (R8 const& lhs, double const& rhs) {
	R8 tmp(lhs);
	tmp -= rhs;
	return tmp;
}
R8 operator* (R8 const& lhs, double const& rhs) {
	R8 tmp(lhs);
	tmp *= rhs;
	return tmp;
}
R8 operator/ (R8 const& lhs, double const& rhs) {
	R8 tmp(lhs);
	tmp /= rhs;
	return tmp;
}
R8 operator+ (double const& lhs, R8 const& rhs) {
	R8 tmp(rhs);
	tmp += lhs;
	return tmp;
}
R8 operator- (double const& lhs, R8 const& rhs) {
	R8 tmp(rhs);
	tmp -= lhs;
	return tmp;
}
R8 operator* (double const& lhs, R8 const& rhs) {
	R8 tmp(rhs);
	tmp *= lhs;
	return tmp;
}
R8 operator/ (double const& lhs, R8 const& rhs) {
	R8 tmp(rhs);
	tmp /= lhs;
	return tmp;
}

std::ostream& operator<< (std::ostream& os, R8 const& r8) {
	os << "R8 { ftl: " << r8.ftl << ", fbl: " << r8.fbl << ", ftr: " << r8.ftr << ", fbr: " << r8.fbr
		<< ", rtl: " << r8.rtl << ", rbr: " << r8.rbr << ", rtr: " << r8.rtr << ", rbr: " << r8.rbr << " }";
	return os;
}
