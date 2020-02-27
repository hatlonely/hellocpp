#include <gtest/gtest.h>
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/container/static_vector.hpp>
#include <iostream>

TEST(testContainer, caseStableVector) {
    // 稳定 vector，使用指针存储元素，随机插入或者删除时，减少元素的拷贝
    boost::container::stable_vector<int> vi({1, 2, 3});

    vi.push_back(4);
    EXPECT_EQ(vi, boost::container::stable_vector<int>({1, 2, 3, 4}));

    vi.pop_back();
    EXPECT_EQ(vi, boost::container::stable_vector<int>({1, 2, 3}));
}

TEST(testContainer, caseStaticVector) {
    // 静态 vector，和数组差不多
    boost::container::static_vector<int, 5> vi({1, 2, 3});

    EXPECT_EQ(vi.size(), 3);
    vi.push_back(4);
    vi.push_back(5);
    EXPECT_EQ(vi.size(), 5);

    EXPECT_THROW(vi.push_back(6), std::bad_alloc);
}

TEST(testContainer, caseSmallVector) {
    // 小 vector，适用于元素个数特别小的场景，超过容量会自动扩容
    boost::container::small_vector<int, 5> vi({1, 2, 3});

    EXPECT_EQ(vi.size(), 3);
    vi.push_back(4);
    vi.push_back(5);
    EXPECT_EQ(vi.size(), 5);

    vi.push_back(6);
    EXPECT_EQ(vi.size(), 6);
}

TEST(testContainer, caseFlatMap) {
    // 使用数组实现的 map，插入时保证顺序，查找直接使用二分
    boost::container::flat_map<std::string, std::string> kvs;

    for (int i = 0; i < 5; i++) {
        kvs["key" + std::to_string(i)] = "val" + std::to_string(i);
    }

    EXPECT_EQ(kvs["key1"], "val1");
    EXPECT_EQ(kvs["key2"], "val2");
    EXPECT_EQ(kvs.count("key6"), 0);
}

TEST(testContainer, caseFlatSet) {
    // 使用数组实现的 set，插入时保证书顺序，查找直接使用二分
    boost::container::flat_set<std::string> keys;

    for (int i = 0; i < 5; i++) {
        keys.insert("key" + std::to_string(i));
    }

    EXPECT_EQ(keys.count("key1"), 1);
    EXPECT_EQ(keys.count("key6"), 0);
}
