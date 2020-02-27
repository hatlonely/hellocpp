#include <gtest/gtest.h>
#include <boost/crc.hpp>
#include <iostream>

TEST(testCRC, case1) {
    boost::crc_ccitt_type crc;
    crc.process_bytes("hello world", 11);
    EXPECT_EQ(crc.checksum(), 61419);
}
