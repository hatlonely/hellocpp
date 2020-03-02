#include <gtest/gtest.h>
#include <iostream>
#include <boost/format.hpp>

TEST(testFormat, case1) {
    std::cout << boost::format("%2% %1%") % 36 % 37 << std::endl;
    std::cout << boost::format("%1$+5d, %2$+5d") % -23 % 35 << std::endl;
}
