#include <gtest/gtest.h>
#include <iostream>
#include <regex>

TEST(testRegex, caseMatch) {
    EXPECT_TRUE(std::regex_match("hello", std::regex("hello")));         // 完全匹配
    EXPECT_TRUE(std::regex_search("hello world", std::regex("hello")));  // 部分匹配
}

TEST(testRegex, caseWildcard) {
    EXPECT_TRUE(std::regex_match("", std::regex("[0-9]*")));
    EXPECT_TRUE(std::regex_match("", std::regex("[0-9]?")));
    EXPECT_TRUE(std::regex_match("1", std::regex("[0-9]?")));
    EXPECT_TRUE(std::regex_match("123", std::regex("[0-9]+")));
    EXPECT_TRUE(std::regex_match("123", std::regex("[0-9]{3}")));
    EXPECT_TRUE(std::regex_match("123", std::regex("[0-9]{3,4}")));
    EXPECT_TRUE(std::regex_match("1234", std::regex("[0-9]{3,4}")));
    EXPECT_TRUE(std::regex_match("1234", std::regex("[0-9]{3,}")));
    EXPECT_TRUE(std::regex_match("123", std::regex("\\d+")));
    EXPECT_TRUE(std::regex_match("\t", std::regex("\\s+")));
    EXPECT_TRUE(std::regex_match("abc", std::regex("\\w+")));
    EXPECT_TRUE(std::regex_match("foo", std::regex("(f|z)oo")));
    EXPECT_TRUE(std::regex_match("zoo", std::regex("(f|z)oo")));
    EXPECT_TRUE(std::regex_match("any thing", std::regex(".*")));
}

TEST(testRegex, caseCapture) {
    {
        std::string str = "hatlonely@foxmail.com";
        std::regex  pattern("^[a-z0-9]+@[a-z0-9.]+[.][a-z]{2,4}$");
        std::smatch result;
        EXPECT_TRUE(std::regex_match(str, result, pattern));
        EXPECT_EQ(result.size(), 1);
        EXPECT_EQ(result[0].str(), "hatlonely@foxmail.com");
    }
    {
        std::string str = "hatlonely@foxmail.com";
        std::regex  pattern("^([a-z0-9]+)@(([a-z0-9.]+)[.]([a-z]{2,4}))$");
        std::smatch result;
        EXPECT_TRUE(std::regex_match(str, result, pattern));
        EXPECT_EQ(result.size(), 5);
        EXPECT_EQ(result[0], "hatlonely@foxmail.com");
        EXPECT_EQ(result[1], "hatlonely");
        EXPECT_EQ(result[2], "foxmail.com");
        EXPECT_EQ(result[3], "foxmail");
        EXPECT_EQ(result[4], "com");
    }
    {
        // ?: 不捕获
        std::string str = "hatlonely@foxmail.com";
        std::regex  pattern("^([a-z0-9]+)@(?:([a-z0-9.]+)[.]([a-z]{2,4}))$");
        std::smatch result;
        EXPECT_TRUE(std::regex_match(str, result, pattern));
        EXPECT_EQ(result.size(), 4);
        EXPECT_EQ(result[0], "hatlonely@foxmail.com");
        EXPECT_EQ(result[1], "hatlonely");
        EXPECT_EQ(result[2], "foxmail");
        EXPECT_EQ(result[3], "com");
    }
    {
        // ?= 正向预测
        std::string str = "Windows 2000";
        std::regex  pattern("Windows (?=95|98|NT|2000)");
        std::smatch result;
        EXPECT_TRUE(std::regex_search(str, result, pattern));
        EXPECT_EQ(result.size(), 1);
        EXPECT_EQ(result[0], "Windows ");
    }
    {
        // ?! 反向预测
        std::string str = "Windows vista";
        std::regex  pattern("Windows (?!95|98|NT|2000)");
        std::smatch result;
        EXPECT_TRUE(std::regex_search(str, result, pattern));
        EXPECT_EQ(result.size(), 1);
        EXPECT_EQ(result[0], "Windows ");
    }
}

TEST(testRegex, caseBackReferences) {
    EXPECT_TRUE(std::regex_match("ab ab", std::regex("(\\w+) \\1")));
    EXPECT_TRUE(std::regex_match("abc abc", std::regex("(\\w+) \\1")));
    EXPECT_FALSE(std::regex_match("abc def", std::regex("(\\w+) \\1")));
}

TEST(testRegex, caseReplace) {
    std::regex pattern("^([a-z0-9]+)@(?:([a-z0-9.]+)[.]([a-z]{2,4}))$");
    EXPECT_EQ(std::regex_replace("hatlonely@foxmail.com", pattern, "$0 $1 $2 $3"), "hatlonely@foxmail.com hatlonely foxmail com");
}

TEST(testRegex, caseFindAll) {
    std::regex               pattern("(\\w+)\\1");
    std::string              str = "abab x acac y aeae";
    std::vector<std::string> vi;
    for (auto it = std::sregex_iterator(str.begin(), str.end(), pattern); it != std::sregex_iterator(); ++it) {
        std::smatch result = *it;
        vi.push_back(result[0]);
    }

    EXPECT_EQ(vi, std::vector<std::string>({"abab", "acac", "aeae"}));
}
