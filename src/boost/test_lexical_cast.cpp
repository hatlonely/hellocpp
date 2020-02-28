#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>
#include <iostream>

TEST(testLexicalCast, case1) {
    EXPECT_EQ(boost::lexical_cast<int>("123456"), 123456);
    EXPECT_NEAR(boost::lexical_cast<double>("123.456"), 123.456, 0.00001);
    EXPECT_EQ(boost::lexical_cast<std::string>(123456), "123456");
    EXPECT_EQ(boost::lexical_cast<std::string>(123.456), "123.456");
}
