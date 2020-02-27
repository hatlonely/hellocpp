#include <gtest/gtest.h>
#include <iostream>
#include <boost/any.hpp>

TEST(testAny, case1) {
    boost::any any;
    
    any = 10;
    EXPECT_EQ(boost::any_cast<int>(any), 10);
    
    any = std::string("hatlonely");
    EXPECT_EQ(boost::any_cast<std::string>(any), "hatlonely");
}

TEST(testAny, case2) {
    std::vector<boost::any> va;
    
    va.push_back(10);
    va.push_back(std::string("hatlonely"));
    
    EXPECT_EQ(va[0].type(), typeid(int));
    EXPECT_EQ(boost::any_cast<int>(va[0]), 10);
    EXPECT_EQ(va[1].type(), typeid(std::string));
    EXPECT_EQ(boost::any_cast<std::string>(va[1]), "hatlonely");
}
