#include <gtest/gtest.h>
#include <iostream>
#include <string>

TEST(testString, case1) {
    {
        std::string str = "stay hungry, stay foolish";
        EXPECT_TRUE(str == "stay hungry, stay foolish");
        EXPECT_TRUE(str.starts_with("stay"));
        EXPECT_TRUE(str.ends_with("foolish"));
        EXPECT_TRUE(str.compare("hello world") > 0);
    }
    {
        EXPECT_EQ(std::string("hello") + " " + "world", "hello world");
        EXPECT_EQ(std::string("0123456789").substr(4), "456789");
        EXPECT_EQ(std::string("0123456789").substr(3, 3), "345");
    }
    {
        EXPECT_EQ(std::string("01234567890123456789").find('6'), 6);
        EXPECT_EQ(std::string("01234567890123456789").rfind('6'), 16);
        EXPECT_EQ(std::string("01234567890123456789").find_first_of('6'), 6);
        EXPECT_EQ(std::string("01234567890123456789").find_last_of('6'), 16);
        EXPECT_EQ(std::string("01234567890123456789").find("678"), 6);
        EXPECT_EQ(std::string("01234567890123456789").rfind("678"), 16);
        EXPECT_EQ(std::string("01234567890123456789").find_first_of("678"), 6);
        EXPECT_EQ(std::string("01234567890123456789").find_last_of("678"), 18);
    }
    {
        EXPECT_EQ(std::stoi("123456"), 123456);
        EXPECT_NEAR(std::stod("123.456"), 123.456, 0.00001);
        EXPECT_EQ(std::to_string(123456), "123456");
        EXPECT_EQ(std::to_string(123.456), "123.456000");
    }
}
