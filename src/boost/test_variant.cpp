#include <gtest/gtest.h>
#include <boost/variant.hpp>
#include <iostream>

class times_two_visitor : public boost::static_visitor<> {
   public:
    void operator()(int &i) const {
        i *= 2;
    }
    void operator()(std::string &str) {
        str += str;
    }
};

TEST(testVariant, case1) {
    boost::variant<int, std::string> u("hello world!");

    EXPECT_EQ(boost::get<std::string>(u), "hello world!");

    times_two_visitor visitor;
    boost::apply_visitor(visitor, u);

    EXPECT_EQ(boost::get<std::string>(u), "hello world!hello world!");
}
