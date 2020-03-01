#include <gtest/gtest.h>
#include <iostream>
#include <boost/static_assert.hpp>

TEST(testStaticAssert, case1) {
    BOOST_STATIC_ASSERT(true);
    BOOST_STATIC_ASSERT_MSG(true, "fail message");
}
