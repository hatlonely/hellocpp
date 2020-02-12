#include <gtest/gtest.h>
#include <iostream>

TEST(testVector, case1) {
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_EQ(vi[2], 3);
        EXPECT_EQ(vi.at(2), 3);
        EXPECT_EQ(vi.front(), 1);
        EXPECT_EQ(vi.back(), 9);
        EXPECT_FALSE(vi.empty());
        EXPECT_EQ(vi.size(), 9);

        for (auto i : vi) {
            std::cout << i << std::endl;
        }

        for (int i = 0; i < vi.size(); i++) {
            EXPECT_EQ(vi[i], i + 1);
        }
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vi.pop_back();
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8}));
        vi.pop_back();
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7}));
        vi.push_back(8);
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8}));
        vi.emplace_back(9);
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vi.insert(vi.cbegin() + 5, 0);
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 0, 6, 7, 8, 9}));
        vi.erase(vi.cbegin() + 5);
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
}
