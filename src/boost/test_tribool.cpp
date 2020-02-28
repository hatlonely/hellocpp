#include <gtest/gtest.h>
#include <boost/logic/tribool.hpp>
#include <iostream>

TEST(testTribool, case1) {
    EXPECT_TRUE(boost::logic::tribool(true));
    EXPECT_TRUE(!boost::logic::tribool(false));
    EXPECT_TRUE(boost::logic::tribool(boost::logic::tribool::indeterminate_value));

    auto b = boost::logic::tribool(true);

    if (b) {
        std::cout << "true" << std::endl;
    } else if (!b) {
        std::cout << "false" << std::endl;
    } else {
        std::cout << "indeterminate" << std::endl;
    }
}
