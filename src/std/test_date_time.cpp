#include <iostream>
#include <gtest/gtest.h>
#include <chrono>

using namespace std::chrono_literals;

TEST(testDuration, case1) {
    auto twoHours = 2h;
    
    EXPECT_EQ(twoHours.count(), 2);
    EXPECT_EQ(std::chrono::minutes(twoHours).count(), 2 * 60);
    EXPECT_EQ(std::chrono::seconds(twoHours).count(), 2 * 60 * 60);
    EXPECT_EQ(std::chrono::milliseconds(twoHours).count(), 2l * 60l * 60l * 1000l);
    EXPECT_EQ(std::chrono::microseconds(twoHours).count(), 2l * 60l * 60l * 1000l * 1000l);
    EXPECT_EQ(std::chrono::nanoseconds(twoHours).count(), 2l * 60l * 60l * 1000l * 1000l * 1000l);
    
    EXPECT_EQ(2h / 2min, 60);
    EXPECT_EQ(2h / 2s, 60 * 60);
    EXPECT_EQ(2h / 2ms, 60l * 60l * 1000l);
    EXPECT_EQ(2h / 2us, 60l * 60l * 1000l * 1000l);
    EXPECT_EQ(2h / 2ns, 60l * 60l * 1000l * 1000l * 1000l);
    
    EXPECT_EQ(std::chrono::round<std::chrono::hours>(2h + 20min), 2h);
    EXPECT_EQ(std::chrono::round<std::chrono::hours>(2h + 40min), 3h);
    EXPECT_EQ(std::chrono::ceil<std::chrono::hours>(2h + 20min), 3h);
    EXPECT_EQ(std::chrono::floor<std::chrono::hours>(2h + 40min), 2h);
}
