#include <gtest/gtest.h>
#include <atomic>
#include <iostream>

TEST(testAtomic, case1) {
    std::atomic<int> i(10);
    i++;
    EXPECT_EQ(i, 11);
    EXPECT_EQ(i.load(), 11);
    
    i = 20;
    EXPECT_EQ(i, 20);
    
    i.store(30);
    EXPECT_EQ(i, 30);
}
