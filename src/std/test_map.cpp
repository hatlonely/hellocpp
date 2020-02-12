#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <unordered_map>

TEST(testMap, case1) {
    {
        std::map<std::string, std::string> m = {
            {"key1", "val1"},
            {"key2", "val2"},
            {"key3", "val3"},
        };

        EXPECT_EQ(m.at("key1"), "val1");
        EXPECT_EQ(m["key2"], "val2");
        EXPECT_FALSE(m.empty());
        EXPECT_EQ(m.size(), 3);
        EXPECT_EQ(m.count("key1"), 1);
        EXPECT_NE(m.find("key1"), m.end());
        EXPECT_EQ(m.find("key1")->second, "val1");
    }
    {
        std::map<std::string, std::string> m;
        m.insert({"key1", "val1"});
        EXPECT_EQ(m.find("key1")->second, "val1");
        m.erase("key1");
        EXPECT_EQ(m.count("key1"), 0);
    }
    {
        std::map<std::string, std::string> m = {
            {"key1", "val1"},
            {"key2", "val2"},
            {"key3", "val3"},
        };
        EXPECT_EQ(m.lower_bound("key1")->second, "val1");  // >= key1
        EXPECT_EQ(m.upper_bound("key1")->second, "val2");  // > key1

        auto p = m.equal_range("key1");
        EXPECT_EQ(p.first->second, "val1");   // >= key1
        EXPECT_EQ(p.second->second, "val2");  // > key1
    }
}

TEST(testUnorderedMap, case1) {
    {
        std::unordered_map<std::string, std::string> m = {
            {"key1", "val1"},
            {"key2", "val2"},
            {"key3", "val3"},
        };

        EXPECT_EQ(m.at("key1"), "val1");
        EXPECT_EQ(m["key2"], "val2");
        EXPECT_FALSE(m.empty());
        EXPECT_EQ(m.size(), 3);
        EXPECT_EQ(m.count("key1"), 1);
        EXPECT_NE(m.find("key1"), m.end());
        EXPECT_EQ(m.find("key1")->second, "val1");
    }
    {
        std::unordered_map<std::string, std::string> m;
        m.insert({"key1", "val1"});
        EXPECT_EQ(m.find("key1")->second, "val1");
        m.erase("key1");
        EXPECT_EQ(m.count("key1"), 0);
    }
}

TEST(testMultiMap, case1) {
    std::multimap<std::string, std::string> m = {
        {"key1", "val1"},
        {"key1", "val2"},
    };
    EXPECT_FALSE(m.empty());
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m.count("key1"), 2);

    m.insert({"key1", "val3"});
    EXPECT_EQ(m.count("key1"), 3);
    m.erase("key1");
    EXPECT_EQ(m.count("key1"), 0);
}

TEST(testUnorderedMultiMap, case1) {
    std::unordered_multimap<std::string, std::string> m = {
        {"key1", "val1"},
        {"key1", "val2"},
    };
    EXPECT_FALSE(m.empty());
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m.count("key1"), 2);

    m.insert({"key1", "val3"});
    EXPECT_EQ(m.count("key1"), 3);
    m.erase("key1");
    EXPECT_EQ(m.count("key1"), 0);
}
