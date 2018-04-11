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

	R3() = default;
	~R3() = default;
	R3(const R3& copy) = default;
	R3(R3&& move) = default;

	R3& operator= (R3 const& rhs) = default;
	R3& operator= (R3&& rhs) = default;

	R3 operator- () const {
		return R3(*this) * -1;
	}
	R3 operator+ () const {
		return R3(*this);
	}

	R3& operator+= (R3 const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] += rhs[i];
		return *this;
	}
	R3& operator-= (R3 const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] -= rhs[i];
		return *this;
	}
	R3& operator*= (R3 const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] *= rhs[i];
		return *this;
	}
	R3& operator/= (R3 const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] /= rhs[i];
		return *this;
	}

	R3& operator+= (double const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] += rhs;
		return *this;
	}
	R3& operator-= (double const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] -= rhs;
		return *this;
	}
	R3& operator*= (double const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] *= rhs;
		return *this;
	}
	R3& operator/= (double const& rhs) {
		for (int i = 0; i < 3; i++) (*this)[i] /= rhs;
		return *this;
	}

	enum class MEMBERS { X = 0, Y = 1, Z = 2 };
	double& operator[](MEMBERS const& index) {
		return v[(int) index];
	}
	const double& operator[](MEMBERS const& index) const {
		return v[(int) index];
	}
	double& operator[](int const& index) {
		return (*this)[static_cast<R3::MEMBERS>(index)];
	}
	const double& operator[](int const& index) const {
		return (*this)[static_cast<R3::MEMBERS>(index)];
	}

	friend bool operator==(R3 const& lhs, R3 const& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}
	friend bool operator!= (R3 const& lhs, R3 const& rhs) {
		return !(lhs == rhs);
	}
	friend bool operator== (R3 const& lhs, double const& rhs) {
		return lhs.x == rhs && lhs.y == rhs && lhs.z == rhs;
	}
	friend bool operator!= (R3 const& lhs, double const& rhs) {
		return !(lhs == rhs);
	}
	friend bool operator== (double const& lhs, R3 const& rhs) {
		return rhs == lhs;
	}
	friend bool operator!= (double const& lhs, R3 const& rhs) {
		return !(rhs == lhs);
	}

	friend R3 operator+ (R3 const& lhs, R3 const& rhs) {
		R3 tmp(lhs);
		tmp += rhs;
		return tmp;
	}
	friend R3 operator- (R3 const& lhs, R3 const& rhs) {
		R3 tmp(lhs);
		tmp -= rhs;
		return tmp;
	}
	friend R3 operator* (R3 const& lhs, R3 const& rhs) {
		R3 tmp(lhs);
		tmp *= rhs;
		return tmp;
	}
	friend R3 operator/ (R3 const& lhs, R3 const& rhs) {
		R3 tmp(lhs);
		tmp /= rhs;
		return tmp;
	}
	friend R3 operator+ (R3 const& lhs, double const& rhs) {
		R3 tmp(lhs);
		tmp += rhs;
		return tmp;
	}
	friend R3 operator- (R3 const& lhs, double const& rhs) {
		R3 tmp(lhs);
		tmp -= rhs;
		return tmp;
	}
	friend R3 operator* (R3 const& lhs, double const& rhs) {
		R3 tmp(lhs);
		tmp *= rhs;
		return tmp;
	}
	friend R3 operator/ (R3 const& lhs, double const& rhs) {
		R3 tmp(lhs);
		tmp /= rhs;
		return tmp;
	}
	friend R3 operator+ (double const& lhs, R3 const& rhs) {
		R3 tmp(rhs);
		tmp += lhs;
		return tmp;
	}
	friend R3 operator- (double const& lhs, R3 const& rhs) {
		R3 tmp(rhs);
		tmp -= lhs;
		return tmp;
	}
	friend R3 operator* (double const& lhs, R3 const& rhs) {
		R3 tmp(rhs);
		tmp *= lhs;
		return tmp;
	}
	friend R3 operator/ (double const& lhs, R3 const& rhs) {
		R3 tmp(rhs);
		tmp /= lhs;
		return tmp;
	}

	friend std::ostream& operator<< (std::ostream& os, R3 const& r3) {
		os << "R3 { x: " << r3.z << ", y: " << r3.y << ", z: " << r3.z << " }";
		return os;
	}

	std::string to_string() {
		auto str = std::string();
		for (auto i : this->v) {
			str += std::to_string(i) + ",";
		}
		str = str.substr(0, str.size() - 1);
		return str;
	}
};

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

	R8() = default;
	~R8() = default;
	R8(const R8& copy) = default;
	R8(R8&& move) = default;

	R8& operator= (R8 const& rhs) = default;
	R8& operator= (R8&& rhs) = default;

	R8 operator- () const {
		return R8(*this) * -1;
	}
	R8 operator+ () const {
		return *this;
	}

	R8& operator+= (R8 const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] += rhs[i];
		return *this;
	}
	R8& operator-= (R8 const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] -= rhs[i];
		return *this;
	}
	R8& operator*= (R8 const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] *= rhs[i];
		return *this;
	}
	R8& operator/= (R8 const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] /= rhs[i];
		return *this;
	}

	R8& operator+= (double const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] += rhs;
		return *this;
	}
	R8& operator-= (double const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] -= rhs;
		return *this;
	}
	R8& operator*= (double const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] *= rhs;
		return *this;
	}
	R8& operator/= (double const& rhs) {
		for (int i = 0; i < 8; i++) (*this)[i] /= rhs;
		return *this;
	}

	enum class MEMBERS { FTL = 0, FBL = 1, FTR = 2, FBR = 3, RTL = 4, RBL = 5, RTR = 6, RBR = 7 };
	double& operator[](MEMBERS const& index) {
		return v[(int) index];
	}
	const double& operator[](MEMBERS const& index) const {
		return v[(int) index];
	}

	double& operator[](int const& index) {
		return (*this)[static_cast<MEMBERS>(index)];
	}
	const double& operator[](int const& index) const {
		return (*this)[static_cast<MEMBERS>(index)];
	}

	friend bool operator== (R8 const& lhs, R8 const& rhs) {
		return lhs.ftl == rhs.ftl && lhs.fbl == rhs.fbl && lhs.ftr == rhs.ftr && lhs.fbr == rhs.fbr
			&& lhs.rtl == rhs.rtl && lhs.rbl == rhs.rbl && lhs.rtr == rhs.rtr && lhs.rbr == rhs.rbr;
	}
	friend bool operator!= (R8 const& lhs, R8 const& rhs) {
		return !(lhs == rhs);
	}
	friend bool operator== (R8 const& lhs, double const& rhs) {
		return lhs.ftl == rhs && lhs.fbl == rhs && lhs.ftr == rhs && lhs.fbr == rhs
			&& lhs.rtl == rhs && lhs.rbl == rhs && lhs.rtr == rhs && lhs.rbr == rhs;
	}
	friend bool operator!= (R8 const& lhs, double const& rhs) {
		return !(lhs == rhs);
	}
	friend bool operator== (double const& lhs, R8 const& rhs) {
		return rhs == lhs;
	}
	friend bool operator!= (double const& lhs, R8 const& rhs) {
		return !(rhs == lhs);
	}

	friend R8 operator+ (R8 const& lhs, R8 const& rhs) {
		R8 tmp(lhs);
		tmp += rhs;
		return tmp;
	}
	friend R8 operator- (R8 const& lhs, R8 const& rhs) {
		R8 tmp(lhs);
		tmp -= rhs;
		return tmp;
	}
	friend R8 operator* (R8 const& lhs, R8 const& rhs) {
		R8 tmp(lhs);
		tmp *= rhs;
		return tmp;
	}
	friend R8 operator/ (R8 const& lhs, R8 const& rhs) {
		R8 tmp(lhs);
		tmp /= rhs;
		return tmp;
	}
	friend R8 operator+ (R8 const& lhs, double const& rhs) {
		R8 tmp(lhs);
		tmp += rhs;
		return tmp;
	}
	friend R8 operator- (R8 const& lhs, double const& rhs) {
		R8 tmp(lhs);
		tmp -= rhs;
		return tmp;
	}
	friend R8 operator* (R8 const& lhs, double const& rhs) {
		R8 tmp(lhs);
		tmp *= rhs;
		return tmp;
	}
	friend R8 operator/ (R8 const& lhs, double const& rhs) {
		R8 tmp(lhs);
		tmp /= rhs;
		return tmp;
	}
	friend R8 operator+ (double const& lhs, R8 const& rhs) {
		R8 tmp(rhs);
		tmp += lhs;
		return tmp;
	}
	friend R8 operator- (double const& lhs, R8 const& rhs) {
		R8 tmp(rhs);
		tmp -= lhs;
		return tmp;
	}
	friend R8 operator* (double const& lhs, R8 const& rhs) {
		R8 tmp(rhs);
		tmp *= lhs;
		return tmp;
	}
	friend R8 operator/ (double const& lhs, R8 const& rhs) {
		R8 tmp(rhs);
		tmp /= lhs;
		return tmp;
	}

	friend std::ostream& operator<< (std::ostream& os, R8 const& r8) {
		os << "R8 { ftl: " << r8.ftl << ", fbl: " << r8.fbl << ", ftr: " << r8.ftr << ", fbr: " << r8.fbr
			<< ", rtl: " << r8.rtl << ", rbr: " << r8.rbr << ", rtr: " << r8.rtr << ", rbr: " << r8.rbr << " }";
		return os;
	}

	std::string to_string() {
		auto str = std::string();
		for (auto i : this->v) {
			str += std::to_string(i) + ",";
		}
		str = str.substr(0, str.size() - 1);
		return str;
	}
};
