#include <gtest/gtest.h>
#include <iostream>
#include <stack>

TEST(testStack, case1) {
    std::stack<int> st;

    for (int i = 0; i < 10; i++) {
        st.push(i);
        EXPECT_EQ(st.top(), i);
    }

    EXPECT_FALSE(st.empty());
    EXPECT_EQ(st.size(), 10);

    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(st.top(), 9 - i);
        st.pop();
    }
}