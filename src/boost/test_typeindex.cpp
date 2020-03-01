#include <gtest/gtest.h>
#include <boost/type_index.hpp>
#include <iostream>

namespace test {
namespace tidx {

class A {};

}
}

TEST(testTypeIndex, case1) {
    std::cout << typeid(test::tidx::A).name() << std::endl;
    std::cout << boost::typeindex::type_id<test::tidx::A>().name() << std::endl;
    std::cout << boost::typeindex::type_id<test::tidx::A>().pretty_name() << std::endl;

    EXPECT_EQ(typeid(test::tidx::A).name(), boost::typeindex::type_id<test::tidx::A>().name());
    EXPECT_EQ(boost::typeindex::type_id<test::tidx::A>().pretty_name(), "test::tidx::A");

    std::cout << typeid(const test::tidx::A).name() << std::endl;
    std::cout << boost::typeindex::type_id<const test::tidx::A>().name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<const test::tidx::A>().name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<const test::tidx::A>().pretty_name() << std::endl;

    EXPECT_EQ(typeid(const test::tidx::A).name(), boost::typeindex::type_id<const test::tidx::A>().name());
    EXPECT_NE(typeid(const test::tidx::A).name(), boost::typeindex::type_id_with_cvr<const test::tidx::A>().name());
    EXPECT_EQ(boost::typeindex::type_id_with_cvr<const test::tidx::A>().pretty_name(), "test::tidx::A const");
}
