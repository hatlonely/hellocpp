#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <vector>

TEST(testNonModifyingSequence, case1) {
    std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_TRUE(std::all_of(vi.begin(), vi.end(), [](int x) { return x > 0; }));
    EXPECT_TRUE(std::any_of(vi.begin(), vi.end(), [](int x) { return x < 5; }));
    EXPECT_TRUE(std::none_of(vi.begin(), vi.end(), [](int x) { return x > 10; }));

    {
        int total = 0;
        std::for_each(vi.begin(), vi.end(), [&total](int x) { total += x; });
        EXPECT_EQ(total, 45);
    }
    {
        EXPECT_EQ(std::count(vi.begin(), vi.end(), 5), 1);
        auto count = std::count_if(vi.begin(), vi.end(), [](int x) { return x % 3 == 0; });
        EXPECT_EQ(count, 3);
    }
    {
        auto it = std::find_if(vi.begin(), vi.end(), [](int x) { return x % 3 == 0; });
        EXPECT_EQ(*it, 3);
    }
    {
        auto it = std::adjacent_find(vi.begin(), vi.end(), [](int x, int y) { return y - x == 1; });
        EXPECT_EQ(*it, 1);
    }
    {
        std::vector<int> vt = {4, 5, 6};
        auto             it = std::search(vi.begin(), vi.end(), vt.begin(), vt.end());
        EXPECT_EQ(*it, 4);
    }
}

TEST(testModifyingSequence, case1) {
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> vt(9, 0);
        std::copy(vi.begin(), vi.end(), vt.begin());
        EXPECT_EQ(vt, vi);
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> vt(15, 0);
        std::copy_backward(vi.begin(), vi.end(), vt.end());
        EXPECT_EQ(vt, std::vector<int>({0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::vector<int> vt(3, 0);
        std::fill(vt.begin(), vt.end(), 6);
        EXPECT_EQ(vt, std::vector<int>({6, 6, 6}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> vt(9, 0);
        std::transform(vi.begin(), vi.end(), vt.begin(), [](int x) { return x * x; });
        EXPECT_EQ(vt, std::vector<int>({1, 4, 9, 16, 25, 36, 49, 64, 81}));
    }
    {
        std::vector<int> vi(5);
        std::generate(vi.begin(), vi.end(), []() { return std::rand() % 10; });
        for (int i = 0; i < 5; i++) {
            std::cout << vi[i] << ", ";
        }
    }
}
