#define BOOST_TEST_MODULE vec_ops
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "vec.h"

BOOST_AUTO_TEST_CASE(vec_init_list) {
	R3 x{0, 0, 0};
	BOOST_CHECK_EQUAL(x.x, 0);
}

BOOST_AUTO_TEST_CASE(vec_zero_list) {
	R3 x{};
	BOOST_CHECK_EQUAL(x.x, 0);
}

BOOST_AUTO_TEST_CASE(vec_sum) {
	R3 x{1, 2, 3};
	R3 y{3, 3, 3};
	auto tsum = x + y;
	R3 sum{4, 5, 6};

	BOOST_CHECK_EQUAL(tsum, sum);
}
