#include <gtest/gtest.h>
#include <iostream>
#include <memory>

TEST(testUniquePtr, case1) {
    auto p = std::make_unique<int>(6);

    EXPECT_EQ(*p, 6);
    EXPECT_FALSE(!p);
}

TEST(testSharedPtr, case1) {
    auto p1 = std::make_shared<int>(6);

    EXPECT_EQ(*p1, 6);
    EXPECT_FALSE(!p1);
    EXPECT_EQ(p1.use_count(), 1);

    {
        auto p2 = p1;
        EXPECT_EQ(p1.use_count(), 2);
        EXPECT_EQ(p2.use_count(), 2);
    }

    EXPECT_EQ(p1.use_count(), 1);
}

TEST(testWeakPtr, case1) {
    auto sp = std::make_shared<int>(6);

    EXPECT_EQ(sp.use_count(), 1);

    auto wp = std::weak_ptr<int>(sp);
    EXPECT_EQ(sp.use_count(), 1);
    EXPECT_EQ(wp.use_count(), 1);

    EXPECT_EQ(*wp.lock(), 6);
    EXPECT_TRUE(!wp.expired());
}
