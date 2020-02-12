#include <gtest/gtest.h>
#include <forward_list>
#include <iostream>

TEST(testForwardList, case1) {
    {
        std::forward_list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_EQ(li.front(), 1);
        EXPECT_FALSE(li.empty());
    }
    {
        std::forward_list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        li.pop_front();
        EXPECT_EQ(li, std::forward_list<int>({2, 3, 4, 5, 6, 7, 8, 9}));
        li.push_front(1);
        EXPECT_EQ(li, std::forward_list<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::forward_list<int> li = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        li.insert_after(std::find(li.begin(), li.end(), 6), 0);
        EXPECT_EQ(li, std::forward_list<int>({1, 2, 3, 4, 5, 6, 0, 7, 8, 9}));
        li.erase_after(std::find(li.begin(), li.end(), 6));
        EXPECT_EQ(li, std::forward_list<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::forward_list<int> l1 = {1, 3, 5, 7};
        std::forward_list<int> l2 = {2, 4, 6, 8};

        l1.merge(l2);
        EXPECT_EQ(l1, std::forward_list<int>({1, 2, 3, 4, 5, 6, 7, 8}));
    }
    {
        std::forward_list<int> l1 = {1, 2, 7, 8};
        std::forward_list<int> l2 = {3, 4, 5, 6};

        auto it = l1.begin();
        std::advance(it, 1);

        l1.splice_after(it, l2);
        EXPECT_EQ(l1, std::forward_list<int>({1, 2, 3, 4, 5, 6, 7, 8}));
    }
}
