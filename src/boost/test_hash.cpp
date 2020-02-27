#include <gtest/gtest.h>
#include <boost/container_hash/hash.hpp>.
#include <iostream>

TEST(testHash, caseBoost) {
    boost::hash<int> ihash;
    std::cout << ihash(123456) << std::endl;
    
    boost::hash<std::string> shash;
    std::cout << shash("123456") << std::endl;
}

TEST(testHash, caseStd) {
    std::hash<int> ihash;
    std::cout << ihash(123456) << std::endl;
    
    std::hash<std::string> shash;
    std::cout << shash("123456") << std::endl;
}
