#include <gtest/gtest.h>
#include <iostream>
#include <list>

TEST(testList, case1) {
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_EQ(li.front(), 1);
        EXPECT_EQ(li.back(), 9);
        EXPECT_FALSE(li.empty());
        EXPECT_EQ(li.size(), 9);
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        li.pop_front();
        EXPECT_EQ(li, std::list<int>({2, 3, 4, 5, 6, 7, 8, 9}));
        li.pop_back();
        EXPECT_EQ(li, std::list<int>({2, 3, 4, 5, 6, 7, 8}));
        li.push_front(1);
        EXPECT_EQ(li, std::list<int>({1, 2, 3, 4, 5, 6, 7, 8}));
        li.emplace_back(9);
        EXPECT_EQ(li, std::list<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        li.insert(std::find(li.begin(), li.end(), 6), 0);
        EXPECT_EQ(li, std::list<int>({1, 2, 3, 4, 5, 0, 6, 7, 8, 9}));
        li.erase(std::find(li.begin(), li.end(), 0));
        EXPECT_EQ(li, std::list<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::list<int> l1 = {1, 3, 5, 7};
        std::list<int> l2 = {2, 4, 6, 8};

        l1.merge(l2);
        EXPECT_EQ(l1, std::list<int>({1, 2, 3, 4, 5, 6, 7, 8}));
    }
    {
        std::list<int> l1 = {1, 2, 7, 8};
        std::list<int> l2 = {3, 4, 5, 6};

        auto it = l1.begin();
        std::advance(it, 2);
        l1.splice(it, l2);
        EXPECT_EQ(l1, std::list<int>({1, 2, 3, 4, 5, 6, 7, 8}));
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        li.reverse();
        EXPECT_EQ(li, std::list<int>({9, 8, 7, 6, 5, 4, 3, 2, 1}));
    }
    {
        std::list<int> li = {8, 7, 4, 5, 3, 6, 1, 3, 4, 9, 2};
        li.sort();
        EXPECT_EQ(li, std::list<int>({1, 2, 3, 3, 4, 4, 5, 6, 7, 8, 9}));
        li.unique();
        EXPECT_EQ(li, std::list<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        li.remove(3);
        EXPECT_EQ(li, std::list<int>({1, 2, 4, 5, 6, 7, 8, 9}));
        li.remove_if([](int x) { return x % 2 == 1; });
        EXPECT_EQ(li, std::list<int>({2, 4, 6, 8}));
    }
}