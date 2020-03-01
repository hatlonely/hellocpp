#include <gtest/gtest.h>
#include <iostream>
#include <boost/signals2/signal.hpp>

void sum(int x, int y) {
    std::cout << "sum: " << x + y << std::endl;
}

void product(int x, int y) {
    std::cout << "product: " << x * y << std::endl;
}

struct difference_t {
    void operator()(int x, int y) const {
        std::cout << "difference: " << x - y << std::endl;
    }
};

TEST(testSignals, case1) {
    boost::signals2::signal<void (int, int)> signal;
    
    signal.connect(sum);
    signal.connect(product);
    signal.connect(difference_t());
    
    signal(7, 4);
}
