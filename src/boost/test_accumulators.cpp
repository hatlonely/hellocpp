#include <gtest/gtest.h>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <iostream>

TEST(testAccumulators, case1) {
    boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;

    acc(1.2);
    acc(2.3);
    acc(3.4);
    acc(4.5);

    EXPECT_EQ(boost::accumulators::mean(acc), 2.85);
}
