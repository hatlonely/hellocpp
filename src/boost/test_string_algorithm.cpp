#include <gtest/gtest.h>
#include <boost/algorithm/string.hpp>
#include <iostream>

TEST(testStringAlgorithm, case1) {
    EXPECT_EQ(boost::to_upper_copy(std::string("hello world")), "HELLO WORLD");
    EXPECT_EQ(boost::trim_copy(std::string(" hello world ")), "hello world");

    std::vector<std::string> vi;
    boost::split(vi, "c++ golang java", boost::is_any_of(" \t\n"));
    EXPECT_EQ(vi, std::vector<std::string>({"c++", "golang", "java"}));
    EXPECT_EQ(boost::join(vi, ", "), "c++, golang, java");

    EXPECT_EQ(boost::replace_first_copy(std::string("hello dolly"), "hello", "goodbye"), "goodbye dolly");
}
