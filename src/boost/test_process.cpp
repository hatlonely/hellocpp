#include <gtest/gtest.h>
#include <boost/process.hpp>
#include <iostream>

TEST(testProcess, case1) {
    boost::process::ipstream out;
    boost::process::child    c("gcc --version", boost::process::std_out > out);

    if (!c.wait_for(std::chrono::seconds(10))) {
        c.terminate();
    }

    while (out) {
        std::string line;
        std::getline(out, line);
        std::cout << line << std::endl;
    }
}
