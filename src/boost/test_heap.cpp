#include <gtest/gtest.h>
#include <boost/heap/priority_queue.hpp>
#include <iostream>

TEST(testHeap, case1) {
    boost::heap::priority_queue<int> pq;

    for (auto i : {3, 6, 5, 7, 9, 0, 4, 8, 1, 2}) {
        pq.push(i);
    }

    EXPECT_FALSE(pq.empty());
    EXPECT_EQ(pq.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(pq.top(), 9 - i);
        pq.pop();
    }
}
