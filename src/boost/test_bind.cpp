#include <gtest/gtest.h>
#include <iostream>
#include <boost/bind.hpp>

namespace test {
namespace bind {
    
TEST(testBind, caseBindFunction) {
    auto add = [](int a, int b) {
        return a + b;
    };
    
    {
        auto add6 = std::bind(add, 6, std::placeholders::_1);
        EXPECT_EQ(add6(4), 10);
    }
}
    
struct A {
    int x = 0;
    
    void add(int a, int b) {
        x += a;
        x += b;
    }
};

TEST(testBind, caseBindMemberFunction) {
    A a;
    
    auto add2 = std::bind(&A::add, std::ref(a), std::placeholders::_1, std::placeholders::_1);
    add2(3);
    EXPECT_EQ(a.x, 6);
    add2(4);
    EXPECT_EQ(a.x, 14);
}
    
}
}

