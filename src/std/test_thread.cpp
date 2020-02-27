#include <gtest/gtest.h>
#include <iostream>
#include <thread>

struct add_function_t {
    void operator()(int a, int b, int &result) {
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        result = a + b;
        std::cout << "add_function_t: " << a << " + " << b << " = " << result << std::endl;
    }
};

TEST(testThread, case1) {
    int a = 1, b = 2, result1, result2;

    std::thread t1([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::cout << "t1" << std::endl;
    });

    std::thread t2([](int a, int b, int &result) {
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        result = a + b;
        std::cout << "add: " << a << " + " << b << " = " << result << std::endl;
    }, a, b, std::ref(result1));

    std::thread t3(add_function_t(), a, b, std::ref(result2));

    t1.join();
    t2.join();
    t3.join();

    EXPECT_EQ(result1, 3);
    EXPECT_EQ(result2, 3);
}

TEST(testThread, caseFunction) {
    std::cout << std::this_thread::get_id() << std::endl;
}
