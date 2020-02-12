#include <gtest/gtest.h>
#include <iostream>
#include <queue>

TEST(testQueue, case1) {
    std::queue<int> queue;

    for (int i = 0; i < 10; i++) {
        queue.push(i);
        EXPECT_EQ(queue.back(), i);
    }

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(queue.front(), i);
        queue.pop();
    }
}
