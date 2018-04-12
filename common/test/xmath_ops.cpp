
#define BOOST_TEST_MODULE xmath_ops
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "common/xmath.hpp"

BOOST_AUTO_TEST_CASE(vec_pos) {
	R<3> x{1, 1, 1};
	x = +x;
	BOOST_CHECK_EQUAL(x[0], 1);
	BOOST_CHECK_EQUAL(x[1], 1);
	BOOST_CHECK_EQUAL(x[2], 1);
}

BOOST_AUTO_TEST_CASE(vec_plus_equal) {
	R<3> x{1, 2, 3};
	R<3> y{1, 2, 3};
	x += y;
	BOOST_CHECK_EQUAL(x[0], 2);
	BOOST_CHECK_EQUAL(x[1], 4);
	BOOST_CHECK_EQUAL(x[2], 6);
}

BOOST_AUTO_TEST_CASE(vec_plus_equal_int) {
	R<3> x{1, 1, 1};
	x += 3;
	BOOST_CHECK_EQUAL(x[0], 4);
	BOOST_CHECK_EQUAL(x[1], 4);
	BOOST_CHECK_EQUAL(x[2], 4);
}

BOOST_AUTO_TEST_CASE(vec_minus_equal_int) {
	R<3> x{1, 1, 1};
	x -= 3;
	BOOST_CHECK_EQUAL(x[0], -2);
	BOOST_CHECK_EQUAL(x[1], -2);
	BOOST_CHECK_EQUAL(x[2], -2);
}

BOOST_AUTO_TEST_CASE(vec_mult_equal_int) {
	R<3> x{1, 1, 1};
	x *= 3;
	BOOST_CHECK_EQUAL(x[0], 3);
	BOOST_CHECK_EQUAL(x[1], 3);
	BOOST_CHECK_EQUAL(x[2], 3);
}

BOOST_AUTO_TEST_CASE(vec_div_equal_int) {
	R<3> x{1, 1, 1};
	x /= 4;
	BOOST_CHECK_EQUAL(x[0], 0.25);
	BOOST_CHECK_EQUAL(x[1], 0.25);
	BOOST_CHECK_EQUAL(x[2], 0.25);
}

BOOST_AUTO_TEST_CASE(vec_plus_equal_double) {
	R<3> x{1, 1, 1};
	x += 1.5;
	BOOST_CHECK_EQUAL(x[0], 2.5);
	BOOST_CHECK_EQUAL(x[1], 2.5);
	BOOST_CHECK_EQUAL(x[2], 2.5);
}

BOOST_AUTO_TEST_CASE(vec_minus_equal_double) {
	R<3> x{1, 1, 1};
	x -= 1.5;
	BOOST_CHECK_EQUAL(x[0], -0.5);
	BOOST_CHECK_EQUAL(x[1], -0.5);
	BOOST_CHECK_EQUAL(x[2], -0.5);
}

BOOST_AUTO_TEST_CASE(vec_mult_equal_double) {
	R<3> x{1, 1, 1};
	x *= 0.5;
	BOOST_CHECK_EQUAL(x[0], 0.5);
	BOOST_CHECK_EQUAL(x[1], 0.5);
	BOOST_CHECK_EQUAL(x[2], 0.5);
}

BOOST_AUTO_TEST_CASE(vec_div_equal_double) {
	R<3> x{1, 1, 1};
	x /= 0.25;
	BOOST_CHECK_EQUAL(x[0], 4);
	BOOST_CHECK_EQUAL(x[1], 4);
	BOOST_CHECK_EQUAL(x[2], 4);
}

BOOST_AUTO_TEST_CASE(vec_equal_vecs) {
	R<3> x{1, 2, 3};
	R<3> y{1, 2, 3};
	BOOST_CHECK(x == y);
}

BOOST_AUTO_TEST_CASE(vec_nequal_vecs) {
	R<3> x{1, 2, 3};
	R<3> y{3, 3, 3};
	BOOST_CHECK(x != y);
}

BOOST_AUTO_TEST_CASE(vec_equal_vec_scalar) {
	R<3> x{3, 3, 3};
	BOOST_CHECK(x == 3);
}

BOOST_AUTO_TEST_CASE(vec_nequal_vec_scalar) {
	R<3> x{1, 2, 3};
	BOOST_CHECK(x != 3);
}

BOOST_AUTO_TEST_CASE(vec_equal_scalar_vec) {
	R<3> x{3, 3, 3};
	BOOST_CHECK(3 == x);
}

BOOST_AUTO_TEST_CASE(vec_nequal_scalar_vec) {
	R<3> x{1, 2, 3};
	BOOST_CHECK(3 != x);
}

BOOST_AUTO_TEST_CASE(vec_math_vec_plus) {
	R<3> x{1, 2, 3};
	R<3> y{3, 2, 1};
	auto z = x + y;
	BOOST_CHECK_EQUAL(z[0], 4);
	BOOST_CHECK_EQUAL(z[1], 4);
	BOOST_CHECK_EQUAL(z[2], 4);
}

BOOST_AUTO_TEST_CASE(vec_math_vec_minus) {
	R<3> x{1, 2, 3};
	R<3> y{3, 2, 1};
	auto z = x - y;
	BOOST_CHECK_EQUAL(z[0], -2);
	BOOST_CHECK_EQUAL(z[1], 0);
	BOOST_CHECK_EQUAL(z[2], 2);
}

BOOST_AUTO_TEST_CASE(vec_math_vec_mult) {
	R<3> x{1, 2, 3};
	R<3> y{3, 2, 1};
	auto z = x * y;
	BOOST_CHECK_EQUAL(z[0], 3);
	BOOST_CHECK_EQUAL(z[1], 4);
	BOOST_CHECK_EQUAL(z[2], 3);
}

BOOST_AUTO_TEST_CASE(vec_math_vec_div) {
	R<3> x{1, 2, 3};
	R<3> y{4, 2, 0};
	auto z = x / y;
	BOOST_CHECK_EQUAL(z[0], 0.25);
	BOOST_CHECK_EQUAL(z[1], 1);
	BOOST_CHECK_EQUAL(z[2], z[2]); // NaN == NaN
}

BOOST_AUTO_TEST_CASE(vec_math_vec_scalar_plus) {
	R<3> x{1, 2, 3};
	auto y = x + 3;
	BOOST_CHECK_EQUAL(y[0], 4);
	BOOST_CHECK_EQUAL(y[1], 5);
	BOOST_CHECK_EQUAL(y[2], 6);
}

BOOST_AUTO_TEST_CASE(vec_math_vec_scalar_minus) {
	R<3> x{1, 2, 3};
	auto y = x - 3;
	BOOST_CHECK_EQUAL(y[0], -2);
	BOOST_CHECK_EQUAL(y[1], -1);
	BOOST_CHECK_EQUAL(y[2], 0);
}

BOOST_AUTO_TEST_CASE(vec_math_vec_scalar_mult) {
	R<3> x{1, 2, 3};
	auto y = x * 3;
	BOOST_CHECK_EQUAL(y[0], 3);
	BOOST_CHECK_EQUAL(y[1], 6);
	BOOST_CHECK_EQUAL(y[2], 9);
}

BOOST_AUTO_TEST_CASE(vec_math_vec_scalar_div) {
	R<3> x{1, 2, 3};
	auto y = x / 4;
	BOOST_CHECK_EQUAL(y[0], 0.25);
	BOOST_CHECK_EQUAL(y[1], 0.5);
	BOOST_CHECK_EQUAL(y[2], 0.75);
}

BOOST_AUTO_TEST_CASE(vec_math_scalar_vec_plus) {
	R<3> x{1, 2, 3};
	auto y = 3 + x;
	BOOST_CHECK_EQUAL(y[0], 4);
	BOOST_CHECK_EQUAL(y[1], 5);
	BOOST_CHECK_EQUAL(y[2], 6);
}

BOOST_AUTO_TEST_CASE(vec_math_scalar_vec_minus) {
	R<3> x{1, 2, 3};
	auto y = 3 - x;
	BOOST_CHECK_EQUAL(y[0], 2);
	BOOST_CHECK_EQUAL(y[1], 1);
	BOOST_CHECK_EQUAL(y[2], 0);
}

BOOST_AUTO_TEST_CASE(vec_math_scalar_vec_mult) {
	R<3> x{1, 2, 3};
	auto y = 3 * x;
	BOOST_CHECK_EQUAL(y[0], 3);
	BOOST_CHECK_EQUAL(y[1], 6);
	BOOST_CHECK_EQUAL(y[2], 9);
}

BOOST_AUTO_TEST_CASE(vec_math_scalar_vec_div) {
	R<3> x{1, 2, 4};
	auto y = 1 / (x / 4);
	BOOST_CHECK_EQUAL(y[0], 4);
	BOOST_CHECK_EQUAL(y[1], 2);
	BOOST_CHECK_EQUAL(y[2], 1);
}

BOOST_AUTO_TEST_CASE(vec_to_string) {
	R<3> x{1, 2, 3};
	auto str = std::to_string(1.0) + ","
		+ std::to_string(2.0) + ","
		+ std::to_string(3.0);
	BOOST_CHECK_EQUAL(x.to_string(), str);
}
