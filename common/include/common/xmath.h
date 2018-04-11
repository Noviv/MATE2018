#ifndef XMATH_H
#define XMATH_H

template<unsigned N>
struct R {
	double v[N];

	constexpr R() = default;
	~R() = default;
	constexpr R(const R&) = default;
	constexpr R(R&&) = default;

	constexpr R& operator=(const R&) = default;
	constexpr R& operator=(R&&) = default;

	constexpr auto operator+() const {
		return R(*this);
	}
 	constexpr auto operator-() const {
		return R(*this) * -1;
	}

	constexpr auto& operator+=(R vec) {
		for (unsigned i = 0; i < N; ++i) v[i] += vec[i];
		return *this;
	}
	constexpr auto& operator-=(R vec) {
		for (unsigned i = 0; i < N; ++i) v[i] -= vec[i];
		return *this;
	}
	constexpr auto& operator*=(R vec) {
		for (unsigned i = 0; i < N; ++i) v[i] *= vec[i];
		return *this;
	}
	constexpr auto& operator/=(R vec) {
		for (unsigned i = 0; i < N; ++i) v[i] /= vec[i];
		return *this;
	}

	template<typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	constexpr auto& operator+=(T s) {
		for (auto& i : v) i += s;
		return *this;
	}
	template<typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	constexpr auto& operator-=(T s) {
		for (auto& i : v) i -= s;
		return *this;
	}
	template<typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	constexpr auto& operator*=(T s) {
		for (auto& i : v) i *= s;
		return *this;
	}
	template<typename T,
		typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	constexpr auto& operator/=(T s) {
		for (auto& i : v) i /= s;
		return *this;
	}

	constexpr auto& operator[](int idx) const {
		return v[idx];
	}

	constexpr auto begin() {
		return &v[0];
	}

	constexpr auto end() {
		return &v[N - 1];
	}

	constexpr std::string to_string() {
		auto str = std::string();
		for (auto i : v) str += std::to_string(i) + ",";
		str = str.substr(0, str.size() - 1);
		return str;
	}
};

/* EQUALITY OPERATORS */
template<unsigned N>
constexpr auto operator==(R<N> lhs, R<N> rhs) {
	for (int i = 0; i < N; ++i) if (lhs[i] != rhs[i]) return false;
	return true;
}

template<unsigned N>
constexpr auto operator!=(R<N> lhs, const R<N> rhs) {
	return !(lhs == rhs);
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator==(R<N> vec, T s) {
	for (auto i : vec) if (i != s) return false;
	return true;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator!=(R<N> vec, T s) {
	return !(vec == s);
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator==(T s, R<N> vec) {
	return vec == s;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator!=(T s, R<N> vec) {
	return !(vec == s);
}

/* MATH OPERATORS */
template<unsigned N>
constexpr auto operator+(R<N> lhs, R<N> rhs) {
	R<N> tmp(lhs);
	tmp += rhs;
	return tmp;
}

template<unsigned N>
constexpr auto operator-(R<N> lhs, R<N> rhs) {
	R<N> tmp(lhs);
	tmp -= rhs;
	return tmp;
}

template<unsigned N>
constexpr auto operator*(R<N> lhs, R<N> rhs) {
	R<N> tmp(lhs);
	tmp *= rhs;
	return tmp;
}

template<unsigned N>
constexpr auto operator/(R<N> lhs, R<N> rhs) {
	R<N> tmp(lhs);
	tmp /= rhs;
	return tmp;
}

/* MATH OPERATORS - VEC SCALAR */
template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator+(R<N> lhs, T s) {
	R<N> tmp(lhs);
	tmp += s;
	return tmp;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator-(R<N> lhs, T s) {
	R<N> tmp(lhs);
	tmp -= s;
	return tmp;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator*(R<N> lhs, T s) {
	R<N> tmp(lhs);
	tmp *= s;
	return tmp;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator/(R<N> lhs, T s) {
	R<N> tmp(lhs);
	tmp /= s;
	return tmp;
}

/* MATH OPERATORS - SCALAR VEC */
template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator+(T s, R<N> rhs) {
	R<N> tmp(rhs);
	tmp += s;
	return tmp;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator-(T s, R<N> rhs) {
	R<N> tmp(rhs);
	for (auto& i : tmp.v) {
		i = s - i;
	}
	return tmp;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator*(T s, R<N> rhs) {
	R<N> tmp(rhs);
	tmp *= s;
	return tmp;
}

template<unsigned N, typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
constexpr auto operator/(T s, R<N> rhs) {
	R<N> tmp(rhs);
	for (auto& i : tmp.v) {
		i = s / i;
	}
	return tmp;
}

#endif
