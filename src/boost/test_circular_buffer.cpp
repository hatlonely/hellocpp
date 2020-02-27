#include <gtest/gtest.h>
#include <boost/circular_buffer.hpp>
#include <iostream>

TEST(testCircularBuffer, case1) {
    boost::circular_buffer<int> cb(3);

    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 1);
    EXPECT_EQ(cb[1], 2);
    EXPECT_EQ(cb[2], 3);

    cb.push_back(4);
    EXPECT_EQ(cb.size(), 3);
    EXPECT_EQ(cb[0], 2);
    EXPECT_EQ(cb[1], 3);
    EXPECT_EQ(cb[2], 4);

    cb.pop_back();
    EXPECT_EQ(cb.size(), 2);
    EXPECT_EQ(cb[0], 2);
    EXPECT_EQ(cb[1], 3);

    cb.pop_front();
    EXPECT_EQ(cb.size(), 1);
    EXPECT_EQ(cb[0], 3);
}
