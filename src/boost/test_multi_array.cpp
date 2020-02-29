#include <gtest/gtest.h>
#include <boost/multi_array.hpp>
#include <iostream>

TEST(testMultiArray, case1) {
    auto ma = boost::multi_array<int, 3>(boost::extents[3][4][5]);

    for (int i = 0; i < ma.shape()[0]; i++) {
        for (int j = 0; j < ma.shape()[1]; j++) {
            for (int k = 0; k < ma.shape()[2]; k++) {
                ma[i][j][k] = i * j * k;
            }
        }
    }

    EXPECT_EQ(ma.num_dimensions(), 3);
    EXPECT_EQ(ma.shape()[0], 3);
    EXPECT_EQ(ma.shape()[1], 4);
    EXPECT_EQ(ma.shape()[2], 5);
    EXPECT_EQ(ma[2][2][2], 8);
}
