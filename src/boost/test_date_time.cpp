#include <gtest/gtest.h>
#include <iostream>
#include <boost/date_time.hpp>

TEST(testDatetime, case1) {
    for (auto d : std::vector<boost::gregorian::date>({
        boost::gregorian::from_string("2020-02-28"),
        boost::gregorian::from_simple_string("2020-Feb-28"),
        boost::gregorian::from_undelimited_string("20200228"),
        boost::gregorian::date_from_iso_string("20200228"),
        boost::gregorian::date(2020,2,28),
        boost::gregorian::date(2020, boost::gregorian::Feb, 28),
    })) {
        EXPECT_EQ(d.year(), 2020);
        EXPECT_EQ(d.month(), boost::gregorian::Feb);
        EXPECT_EQ(d.month().as_number(), 2);
        EXPECT_EQ(d.day(), 28);
        EXPECT_EQ(d.day_of_year(), 59);
        EXPECT_EQ(d.day_of_week(), boost::gregorian::Friday);
        EXPECT_EQ(d.day_of_week().as_number(), 5);
        EXPECT_EQ(d.week_number(), 9);
        EXPECT_EQ(d.day_number(), 2458908);
    }
    
    {
        auto today = boost::gregorian::day_clock::local_day();
        std::cout << "today: " << today << std::endl;
    }
    
    {
        auto d1 = boost::gregorian::date(2020, 2, 28);
        auto d2 = d1 + boost::gregorian::months(1);
        
        for (auto d = d1; d != d2; d += boost::gregorian::days(1)) {
            std::cout << d << std::endl;
        }
    }
}
