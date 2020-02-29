#include <gtest/gtest.h>
#include <iostream>
#include <boost/predef.h>

TEST(testPredef, case1) {
    if (BOOST_COMP_GNUC) {
        std::cout << "this is gnu gcc" << std::endl;
    }
    if (BOOST_COMP_CLANG) {
        std::cout << "this is clang" << std::endl;
    }
    if (BOOST_OS_IOS) {
        std::cout << "this is ios" << std::endl;
    }
    if (BOOST_OS_BSD) {
        std::cout << "this is bsd" << std::endl;
    }
    if (BOOST_OS_UNIX) {
        std::cout << "this is unix" << std::endl;
    }
    if (BOOST_OS_MACOS) {
        std::cout << "this is mac os" << std::endl;
    }
    if (BOOST_OS_LINUX) {
        std::cout << "this is linux" << std::endl;
    }
    if (BOOST_PLAT_ANDROID) {
        std::cout << "this is android" << std::endl;
    }
    if (BOOST_PLAT_IOS_DEVICE) {
        std::cout << "this is ios devide" << std::endl;
    }
}
