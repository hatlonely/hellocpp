#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

TEST(testNonModifyingSequenceAlgorithm, case1) {
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

TEST(testModifyingSequenceAlgorithm, case1) {
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> vo(9, 0);
        std::copy(vi.begin(), vi.end(), vo.begin());
        EXPECT_EQ(vo, vi);
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> vo(15, 0);
        std::copy_backward(vi.begin(), vi.end(), vo.end());
        EXPECT_EQ(vo, std::vector<int>({0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }
    {
        std::vector<int> vi(3, 0);
        std::fill(vi.begin(), vi.end(), 6);
        EXPECT_EQ(vi, std::vector<int>({6, 6, 6}));
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
        std::cout << "generate: ";
        std::copy(vi.begin(), vi.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 3};
        std::remove(vi.begin(), vi.end(), 3);
        EXPECT_EQ(vi, std::vector<int>({1, 2, 4, 5, 5, 3}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5};
        std::remove_if(vi.begin(), vi.end(), [](int x) { return x % 2 == 0; });
        EXPECT_EQ(vi, std::vector<int>({1, 3, 5, 4, 5}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 3};
        std::replace(vi.begin(), vi.end(), 3, 6);
        EXPECT_EQ(vi, std::vector<int>({1, 2, 6, 4, 5, 6}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5};
        std::reverse(vi.begin(), vi.end());
        EXPECT_EQ(vi, std::vector<int>({5, 4, 3, 2, 1}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5};
        std::rotate(vi.begin(), vi.begin() + 1, vi.end());
        EXPECT_EQ(vi, std::vector<int>({2, 3, 4, 5, 1}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5};
        std::rotate(vi.rbegin(), vi.rbegin() + 1, vi.rend());
        EXPECT_EQ(vi, std::vector<int>({5, 1, 2, 3, 4}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5};
        std::shuffle(vi.begin(), vi.end(), std::default_random_engine());
        std::cout << "shuffle: ";
        std::copy(vi.begin(), vi.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> vo(5);
        std::sample(vi.begin(), vi.end(), vo.begin(), 3, std::default_random_engine());
        std::cout << "sample: ";
        std::copy(vo.begin(), vo.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << std::endl;
    }
    {
        std::vector<int> vi = {1, 1, 2, 3, 2, 3};
        std::unique(vi.begin(), vi.end());
    }
}

TEST(testSortAlgorithm, case1) {
    {
        std::vector<int> vi = {4, 3, 6, 5, 8, 1, 2, 9, 7};
        std::sort(vi.begin(), vi.end(), std::less<int>());
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
        EXPECT_TRUE(std::is_sorted(vi.begin(), vi.end(), std::less<int>()));
    }
    {
        std::vector<int> vi = {4, 3, 6, 5, 8, 1, 2, 9, 7};
        std::nth_element(vi.begin(), vi.begin() + 3, vi.end());
        EXPECT_EQ(*(vi.begin() + 3), 4);
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_EQ(*std::lower_bound(vi.begin(), vi.end(), 6), 6);
        EXPECT_EQ(*std::upper_bound(vi.begin(), vi.end(), 6), 7);
        EXPECT_TRUE(std::binary_search(vi.begin(), vi.end(), 4));
    }
    {
        std::vector<int> v1 = {1, 3, 4, 6};
        std::vector<int> v2 = {2, 5, 7, 8};
        std::vector<int> vo(8);
        std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vo.begin());
        EXPECT_EQ(vo, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8}));
    }
}

TEST(testSetAlgorithm, case1) {
    std::set<int> s1 = {1, 2, 3, 4};
    std::set<int> s2 = {3, 4, 5, 6};

    EXPECT_FALSE(std::includes(s1.begin(), s1.end(), s2.begin(), s2.end()));

    {
        std::vector<int> so(2);
        std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), so.begin());
        EXPECT_EQ(so, std::vector<int>({1, 2}));
    }
    {
        std::vector<int> so(2);
        std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), so.begin());
        EXPECT_EQ(so, std::vector<int>({3, 4}));
    }
    {
        std::vector<int> so(6);
        std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), so.begin());
        EXPECT_EQ(so, std::vector<int>({1, 2, 3, 4, 5, 6}));
    }
}

TEST(testMaxMinAlgorithm, case1) {
    std::vector<int> vi = {4, 3, 6, 5, 8, 1, 2, 9, 7};
    EXPECT_EQ(*std::max_element(vi.begin(), vi.end()), 9);
    EXPECT_EQ(*std::min_element(vi.begin(), vi.end()), 1);
}

TEST(testPermutationAlgorithm, case1) {
    std::vector<int> vi = {1, 2, 3, 4};
    std::next_permutation(vi.begin(), vi.end());
    EXPECT_EQ(vi, std::vector<int>({1, 2, 4, 3}));
    std::prev_permutation(vi.begin(), vi.end());
    EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 4}));
}

TEST(testNumericAlgorithm, case1) {
    {
        std::vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        EXPECT_EQ(std::accumulate(vi.begin(), vi.end(), 0), 45);
        EXPECT_EQ(std::accumulate(vi.begin(), vi.end(), 1, std::multiplies<>()), 362880);
    }
    {
        std::vector<int> v1 = {0, 1, 2, 3, 4};
        std::vector<int> v2 = {5, 4, 2, 3, 1};
        EXPECT_EQ(std::inner_product(v1.begin(), v1.end(), v2.begin(), 0), 21);
    }
    {
        std::vector<int> vi = {1, 3, 6, 8};
        std::adjacent_difference(vi.begin(), vi.end(), vi.begin());
        EXPECT_EQ(vi, std::vector<int>({1, 2, 3, 2}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5};
        std::partial_sum(vi.begin(), vi.end(), vi.begin());
        EXPECT_EQ(vi, std::vector<int>({1, 3, 6, 10, 15}));
    }
    {
        std::vector<int> vi = {1, 2, 3, 4, 5};
        std::partial_sum(vi.begin(), vi.end(), vi.begin(), std::multiplies<>());
        EXPECT_EQ(vi, std::vector<int>({1, 2, 6, 24, 120}));
    }
}
