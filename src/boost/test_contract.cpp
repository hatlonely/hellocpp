#include <gtest/gtest.h>
#include <boost/contract.hpp>
#include <iostream>
#include <numeric>

namespace test {
namespace contract {

TEST(testContract, case1) {
    auto inc = [](int &x) {
        boost::contract::old_ptr<int> oldx  = BOOST_CONTRACT_OLDOF(x);
        boost::contract::check        check = boost::contract::function()
                                           .precondition([&] {
                                               BOOST_CONTRACT_ASSERT(x < std::numeric_limits<int>::max());
                                           })
                                           .postcondition([&] {
                                               BOOST_CONTRACT_ASSERT(x == *oldx + 1);
                                           });

        ++x;
    };

    int x = 0;
    inc(x);
}
}
}
