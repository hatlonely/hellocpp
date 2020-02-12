#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include <unordered_set>

TEST(testSet, case1) {
    {
        std::set<int> si = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_FALSE(si.empty());
        EXPECT_EQ(si.size(), 9);

        EXPECT_EQ(si.count(0), 0);
        EXPECT_EQ(si.count(1), 1);
        EXPECT_EQ(si.find(0), si.end());
        EXPECT_NE(si.find(1), si.end());
    }
    {
        std::set<int> si = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        si.insert(0);
        EXPECT_EQ(si, std::set<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}));
        si.erase(0);
        EXPECT_EQ(si, std::set<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::set<int> si = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_EQ(*si.lower_bound(6), 6);  // >= 6
        EXPECT_EQ(*si.upper_bound(6), 7);  // > 6

        auto p = si.equal_range(6);
        EXPECT_EQ(*p.first, 6);   // >= 6
        EXPECT_EQ(*p.second, 7);  // > 6
    }
}

TEST(testMultiSet, case1) {
    {
        std::multiset<int> si = {1, 1, 1, 2, 3, 3, 4, 4, 5};
        EXPECT_FALSE(si.empty());
        EXPECT_EQ(si.size(), 9);
        EXPECT_EQ(si.count(1), 3);

        si.insert(1);
        EXPECT_EQ(si.count(1), 4);
        si.erase(1);
        EXPECT_EQ(si.count(1), 0);
    }
}

TEST(testUnorderedSet, case1) {
    {
        std::unordered_set<int> si = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_FALSE(si.empty());
        EXPECT_EQ(si.size(), 9);

        EXPECT_EQ(si.count(0), 0);
        EXPECT_EQ(si.find(0), si.end());
    }
    {
        std::unordered_set<int> si = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        si.insert(0);
        EXPECT_EQ(si, std::unordered_set<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}));
        si.erase(0);
        EXPECT_EQ(si, std::unordered_set<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::unordered_set<int> si = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        si.rehash(100);
        EXPECT_NEAR(si.load_factor(), 0.1, 0.001);
        EXPECT_EQ(si.max_load_factor(), 1);
    }
}
