#include <gtest/gtest.h>
#include <iostream>
#include <set>

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
    }
    {
        std::set<int> si = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto          p  = si.equal_range(6);
        EXPECT_EQ(*p.first, 6);   // >= 6
        EXPECT_EQ(*p.second, 7);  // > 6
    }
}