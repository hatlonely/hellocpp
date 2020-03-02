#include <gtest/gtest.h>
#include <iostream>
#include <curl/curl.h>

TEST(testLibcurl, case1) {
    std::cout << curl_version() << std::endl;
}
