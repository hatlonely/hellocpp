#include <gtest/gtest.h>
#include <chrono>
#include <iostream>

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

TEST(testClock, case1) {
    {
        // 系统时间，随系统时间改变而变化，受到时间调整的影响
        auto start = std::chrono::system_clock::now();
        auto end   = std::chrono::system_clock::now();
        std::cout << (end - start).count() << std::endl;

        // 转时间戳
        std::cout << std::chrono::system_clock::to_time_t(start) << std::endl;
    }
    {
        // 稳定的时间，保证递增
        auto start = std::chrono::steady_clock::now();
        auto end   = std::chrono::steady_clock::now();
        std::cout << (end - start).count() << std::endl;
    }
    {
        // 高精度时间，通常是 system_clock 或者 steady_clock 的别名，应尽量避免使用
        auto start = std::chrono::high_resolution_clock::now();
        auto end   = std::chrono::high_resolution_clock::now();
        std::cout << (end - start).count() << std::endl;
    }
}
