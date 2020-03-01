#include <gtest/gtest.h>
#include <boost/algorithm/hex.hpp>
#include <iostream>

TEST(testAlgorithm, case1) {
    EXPECT_EQ(boost::algorithm::hex(std::string("abcdef")), "616263646566");
    EXPECT_EQ(boost::algorithm::unhex(std::string("616263646566")), "abcdef");
}
