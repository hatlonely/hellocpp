#include <gtest/gtest.h>
#include <boost/bimap.hpp>
#include <iostream>

TEST(testBimap, case1) {
    boost::bimap<std::string, std::string>                     bm;
    typedef boost::bimap<std::string, std::string>::value_type ValueType;

    bm.insert(ValueType("key1", "val1"));
    bm.insert(ValueType("key2", "val2"));
    bm.insert(ValueType("key3", "val3"));
    bm.insert(ValueType("key4", "val4"));

    EXPECT_EQ(bm.left.at("key1"), "val1");
    EXPECT_EQ(bm.left.at("key2"), "val2");
    EXPECT_EQ(bm.right.at("val1"), "key1");
    EXPECT_EQ(bm.right.at("val2"), "key2");
}
