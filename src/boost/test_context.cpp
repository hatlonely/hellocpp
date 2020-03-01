#include <gtest/gtest.h>
#include <boost/context/fiber.hpp>
#include <iostream>

TEST(testContext, case1) {
    int                   m;
    boost::context::fiber source = {
        [&m](boost::context::fiber&& sink) {
            m     = 0;
            int n = 1;
            while (true) {
                sink = std::move(sink).resume();

                int next = m + n;
                m        = n;
                n        = next;
            }
            return std::move(sink);
        }};

    for (int i = 0; i < 10; i++) {
        source = std::move(source).resume();
        std::cout << m << std::endl;
    }
}

TEST(testContext, case2) {
    int                   m  = 0;
    boost::context::fiber f1 = {
        [&m](boost::context::fiber&& f2) {
            std::cout << "f1: entered 1st time " << m << std::endl;
            m += 1;
            f2 = std::move(f2).resume();
            std::cout << "f1: entered 2nd time " << m << std::endl;
            m += 1;
            f2 = std::move(f2).resume();
            std::cout << "f1: entered 3rd time " << m << std::endl;
            return std::move(f2);
        }};

    f1 = std::move(f1).resume();
    std::cout << "f1: return 1st time" << m << std::endl;
    m += 1;
    f1 = std::move(f1).resume();
    std::cout << "f1: return 2nd time" << m << std::endl;
    m += 1;
    std::cout << "f1: returned 3rd time" << std::endl;
}
