#include <gtest/gtest.h>
#include <boost/signals2/signal.hpp>
#include <iostream>

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
    boost::signals2::signal<void(int, int)> signal;

    signal.connect(sum);
    signal.connect(product);
    signal.connect(difference_t());

    signal(7, 4);
}

int add(int x, int y) {
    return x + y;
}

int mul(int x, int y) {
    return x * y;
}

int sub(int x, int y) {
    return x - y;
}

template <typename T>
struct maxi {
    typedef T result_type;
    template <typename It>
    T operator()(It begin, It end) const {
        if (begin == end) {
            return T();
        }

        auto v = *begin++;
        for (auto i = begin; i != end; ++i) {
            if (v < *i) {
                v = *i;
            }
        }

        return v;
    }
};

TEST(testSignals, case2) {
    boost::signals2::signal<int(int, int), maxi<int>> signal;

    signal.connect(add);
    signal.connect(mul);
    signal.connect(sub);

    EXPECT_EQ(signal(7, 4), 28);
}
