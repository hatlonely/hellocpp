#include <gtest/gtest.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

TEST(testMath, case1) {
    EXPECT_EQ(std::abs(-6), 6);
    EXPECT_EQ(std::floor(-6.2), -7);  // 向下取整
    EXPECT_EQ(std::floor(6.2), 6);
    EXPECT_EQ(std::floor(6.8), 6);
    EXPECT_EQ(std::ceil(-6.2), -6);  // 向上取整
    EXPECT_EQ(std::ceil(6.2), 7);
    EXPECT_EQ(std::ceil(6.8), 7);
    EXPECT_EQ(std::round(-6.2), -6);  // 四舍五入，远离原点
    EXPECT_EQ(std::round(6.2), 6);
    EXPECT_EQ(std::round(6.8), 7);
    EXPECT_EQ(std::round(6.5), 7);
    EXPECT_EQ(std::round(-6.5), -7);
    EXPECT_EQ(std::trunc(-6.2), -6);  // 靠近原点取整
    EXPECT_EQ(std::trunc(6.2), 6);
    EXPECT_EQ(std::trunc(6.8), 6);
    EXPECT_EQ(std::trunc(6.5), 6);
    EXPECT_EQ(std::trunc(-6.5), -6);
    // 四舍五入，通过 std::fesetround(FE_TONEAREST) 设置舍入模式
    // 包括，FE_DOWNWARD(向下舍入)，FE_UPWARD(向上舍入)，FE_TONEAREST(远离原点)，FE_TOWARDZERO(靠近原点)
    // 默认为靠近原点
    EXPECT_EQ(std::nearbyint(-6.2), -6);
    EXPECT_EQ(std::nearbyint(6.2), 6);
    EXPECT_EQ(std::nearbyint(6.8), 7);
    EXPECT_EQ(std::nearbyint(6.5), 6);
    EXPECT_EQ(std::nearbyint(-6.5), -6);
    // 和 nearbyint 一样，处理异常值(比如溢出)的方式略有不同，rint 会抛出异常
    EXPECT_EQ(std::rint(-6.2), -6);
    EXPECT_EQ(std::rint(6.2), 6);
    EXPECT_EQ(std::rint(6.8), 7);
    EXPECT_EQ(std::rint(6.5), 6);
    EXPECT_EQ(std::rint(-6.5), -6);

    EXPECT_EQ(std::remainder(7, 3), 1);
    EXPECT_EQ(std::remainder(-7, 3), -1);
    EXPECT_EQ(std::remainder(7, -3), 1);

    const auto abs_error = 0.00001;

    EXPECT_NEAR(std::sin(M_PI_2), 1, abs_error);
    EXPECT_NEAR(std::cos(M_PI), -1, abs_error);
    EXPECT_NEAR(std::tan(M_PI_4), 1, abs_error);
    EXPECT_NEAR(std::asin(1), M_PI_2, abs_error);
    EXPECT_NEAR(std::acos(-1), M_PI, abs_error);
    EXPECT_NEAR(std::atan(1), M_PI_4, abs_error);
    EXPECT_NEAR(std::atan2(1, 4), std::atan(0.25), abs_error);

    EXPECT_NEAR(std::pow(3, 2), 9, abs_error);
    EXPECT_NEAR(std::pow(2, 3), 8, abs_error);
    EXPECT_NEAR(std::sqrt(4), 2, abs_error);
    EXPECT_NEAR(std::cbrt(27), 3, abs_error);
    EXPECT_NEAR(std::hypot(3, 4), 5, abs_error);  // √(x² + y²)

    EXPECT_NEAR(std::exp(2.5), std::pow(M_E, 2.5), abs_error);  // e ^ x
    EXPECT_NEAR(std::exp2(10), 1024, abs_error);                // 2 ^ x
    EXPECT_NEAR(std::expm1(2), std::exp(2) - 1, abs_error);     // e ^ x - 1
    EXPECT_NEAR(std::log(std::exp(1.5)), 1.5, abs_error);       // ln(x)
    EXPECT_NEAR(std::log10(1000), 3, abs_error);                // lg(x)
    EXPECT_NEAR(std::log2(1024), 10, abs_error);
    EXPECT_NEAR(std::log1p(2), std::log(2 + 1), abs_error);

    EXPECT_NEAR(std::sinh(2), (std::exp(2) - std::exp(-2)) / 2, abs_error);  // sinh(x) = (e ^ x - e ^ -x) / 2
    EXPECT_NEAR(std::cosh(2), (std::exp(2) + std::exp(-2)) / 2, abs_error);  // cosh(x) = (e ^ x + e ^ -x) / 2
    EXPECT_NEAR(std::tanh(2), std::sinh(2) / std::cosh(2), abs_error);       // tanh(x) = sinh(x) / cosh(x)

    EXPECT_NEAR(std::erf(0.4), 0.42839235504666845, abs_error);  // 误差函数
    EXPECT_NEAR(std::erfc(0.4), 0.5716076449533315, abs_error);  // 余补误差函数
    EXPECT_NEAR(std::tgamma(6), 5 * 4 * 3 * 2 * 1, abs_error);   // 伽马函数
}
