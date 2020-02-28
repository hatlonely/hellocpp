#include <gtest/gtest.h>
#include <iostream>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/stack.hpp>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

using namespace std::chrono_literals;

TEST(testLockfree, caseQueue) {
    auto queue = boost::lockfree::queue<int>(10);
    
    std::vector<std::thread> ps(10);
    std::vector<std::thread> cs(20);
    
    auto rd = std::random_device();
    auto now = std::chrono::system_clock::now();
    
    for (int i = 0; i < ps.size(); i++) {
        ps[i] = std::thread([&queue, &rd, &now]{
            while (std::chrono::system_clock::now() - now < 500ms) {
                int i = rd() % 10;
                if (queue.push(i)) {
                    std::cout << "produce " << i << std::endl;
                }
            }
        });
    }
    
    for (int i = 0; i < cs.size(); i++) {
        cs[i] = std::thread([&queue, &rd, &now]{
            while (std::chrono::system_clock::now() - now < 500ms) {
                int i = 0;
                if (queue.pop(i)) {
                    std::cout << "consume " << i << std::endl;
                }
            }
        });
    }
    
    for (int i = 0; i < ps.size(); i++) {
        ps[i].join();
    }
    
    for (int i = 0; i < cs.size(); i++) {
        cs[i].join();
    }
}

TEST(testLockfree, caseStack) {
    auto stack = boost::lockfree::stack<int>(10);
    
    std::vector<std::thread> ps(10);
    std::vector<std::thread> cs(10);
    
    auto rd = std::random_device();
    auto now = std::chrono::system_clock::now();
    
    for (int i = 0; i < ps.size(); i++) {
        ps[i] = std::thread([&stack, &rd, &now]{
            while (std::chrono::system_clock::now() - now < 500ms) {
                int i = rd() % 10;
                if (stack.push(i)) {
                    std::cout << "produce " << i << std::endl;
                }
            }
        });
    }
    
    for (int i = 0; i < cs.size(); i++) {
        cs[i] = std::thread([&stack, &rd, &now]{
            while (std::chrono::system_clock::now() - now < 500ms) {
                int i = 0;
                if (stack.pop(i)) {
                    std::cout << "consume " << i << std::endl;
                }
            }
        });
    }
    
    for (int i = 0; i < ps.size(); i++) {
        ps[i].join();
    }
    
    for (int i = 0; i < cs.size(); i++) {
        cs[i].join();
    }
}
