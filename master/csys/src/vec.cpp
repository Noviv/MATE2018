#include "vec.h"

R3& R3::operator= (R3 const& rhs) {
    if (this != &rhs) {
        std::memcpy(rhs.v, this->v, 3 * sizeof(double));
    }
    return *this;
}
R3& R3::operator= (R3&& rhs) {
    std::memcpy(rhs.v, this->v, 3 * sizeof(double));
    std::memset(rhs.v, 3, sizeof(double));
    return *this;
}

R3 R3::operator- () const {
    return R3 {-this->R3, -this->y, -this->z};
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
R3& R3::operator%= (R3 const& rhs) {
    for (int i = 0; i < 3; i++) (*this)[i] %= rhs[i];
    return *this;
}

double& R3::operator[](R3::MEMBERS const& index) {
    return v[index];
}
const double& R3::operator[](R3::MEMBERS const& index) const {
    return v[index];
}

double& R3::operator[](unsigned int const& index) {
    return (*this)[std::static_cast<R3::MEMBERS>(index)];
}
const double& R3::operator[](unsigned int const& index) const {
    return (*this)[std::static_cast<R3::MEMBERS>(index)];
}

bool operator== (X const& lhs, X const& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
bool operator!= (X const& lhs, X const& rhs) {
    return !(lhs == rhs);
}
bool operator== (X const& lhs, double const& rhs) {
    return lhs.x == rhs && lhs.y == rhs && lhs.z == rhs;
}
bool operator!= (X const& lhs, double const& rhs) {
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
R3 operator% (R3 const& lhs, R3 const& rhs) {
    R3 tmp(lhs);
    tmp %= rhs;
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
R3 operator% (R3 const& lhs, double const& rhs) {
    R3 tmp(lhs);
    tmp %= rhs;
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
R3 operator% (double const& lhs, R3 const& rhs) {
    R3 tmp(rhs);
    tmp %= lhs;
    return tmp;
}

ostream& operator<< (ostream& os, R3 const& r3) {
    os << "R3 { x: " << r3.z << ", y: " << r3.y << ", z: " << r3.z << " }";
    return os;
}

// Redo the exact same thing for R8

R8& R8::operator= (R8 const& rhs) {
    if (this != &rhs) {
        std::memcpy(rhs.v, this->v, 8 * sizeof(double));
    }
    return *this;
}
R8& R8::operator= (R8&& rhs) {
    std::memcpy(rhs.v, this->v, 8 * sizeof(double));
    std::memset(rhs.v, 8, sizeof(double));
    return *this;
}

R8 R8::operator- () const {
    return R8 {-this->R8, -this->y, -this->z};
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
R8& R8::operator%= (R8 const& rhs) {
    for (int i = 0; i < 8; i++) (*this)[i] %= rhs[i];
    return *this;
}

double& R8::operator[](R8::MEMBERS const& index) {
    return v[index];
}
const double& R8::operator[](R8::MEMBERS const& index) const {
    return v[index];
}

double& R8::operator[](unsigned int const& index) {
    return (*this)[std::static_cast<R8::MEMBERS>(index)];
}
const double& R8::operator[](unsigned int const& index) const {
    return (*this)[std::static_cast<R8::MEMBERS>(index)];
}

bool operator== (R8 const& lhs, R8 const& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}
bool operator!= (R8 const& lhs, R8 const& rhs) {
    return !(lhs == rhs);
}
bool operator== (R8 const& lhs, double const& rhs) {
    return lhs.x == rhs && lhs.y == rhs && lhs.z == rhs;
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
R8 operator% (R8 const& lhs, R8 const& rhs) {
    R8 tmp(lhs);
    tmp %= rhs;
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
R8 operator% (R8 const& lhs, double const& rhs) {
    R8 tmp(lhs);
    tmp %= rhs;
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
R8 operator% (double const& lhs, R8 const& rhs) {
    R8 tmp(rhs);
    tmp %= lhs;
    return tmp;
}

ostream& operator<< (ostream& os, R8 const& r8) {
    os << "R8 { ftl: " << r8.ftl << ", fbl: " << r8.fbl << ", ftr: " << r8.ftr << ", fbr: " << r3.fbr << ", rtl: " << r3.rtl << ", rbr: " << r3.rbr << ", rtr: " << r3.rtr << ", rbr: " << r3.rbr << " }";
    return os;
}