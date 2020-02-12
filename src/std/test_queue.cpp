#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <deque>

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

TEST(testPriorityQueue, case1) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> queue;

    for (auto i : {3, 6, 5, 7, 9, 0, 4, 8, 1, 2}) {
        queue.push(i);
    }

    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(queue.top(), i);
        queue.pop();
    }
}

TEST(testDeque, case1) {
    std::deque<int> deque = {2, 3, 4, 5, 6, 7, 8};

    deque.push_front(1);
    deque.push_back(9);

    EXPECT_EQ(deque.front(), 1);
    EXPECT_EQ(deque.back(), 9);
}