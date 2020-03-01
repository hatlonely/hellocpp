#include <gtest/gtest.h>
#include <boost/typeof/typeof.hpp>
#include <iostream>

// c++11 之后使用 decltype 和 auto 关键字即可
TEST(testTypeOf, case1) {
    typedef BOOST_TYPEOF(1 + 0.5) type;
    EXPECT_TRUE((std::is_same<type, double>::value));

    BOOST_AUTO(p, std::make_pair(1, 2));
    EXPECT_TRUE((std::is_same<BOOST_TYPEOF(p), std::pair<int, int>>::value));
    EXPECT_TRUE((std::is_same<decltype(p), std::pair<int, int>>::value));
}
