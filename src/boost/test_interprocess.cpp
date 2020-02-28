#include <gtest/gtest.h>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>
#include <map>
#include <string>
#include <thread>

using namespace std::chrono_literals;

TEST(testInterprocess, caseSharedMemory1) {
    auto t1 = std::thread([] {
        auto segment = boost::interprocess::managed_shared_memory(boost::interprocess::create_only, "MySharedMemory1", 65536);
        int* pi      = segment.construct<int>("i")(10);
        int* pa      = segment.construct<int>("a")[3](0);
        pa[0]        = 1;
        pa[1]        = 2;
        pa[2]        = 3;
    });
    t1.join();

    auto t2 = std::thread([] {
        auto segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, "MySharedMemory1");
        {
            auto it = segment.find<int>("i");
            EXPECT_EQ(*it.first, 10);
        }
        {
            auto it = segment.find<int>("a");
            EXPECT_EQ(it.first[0], 1);
            EXPECT_EQ(it.first[1], 2);
            EXPECT_EQ(it.first[2], 3);
        }

        segment.destroy<int>("i");
        segment.destroy<int>("a");
    });
    t2.join();

    boost::interprocess::shared_memory_object::remove("MySharedMemory1");
}

TEST(testInterprocess, caseSharedMemory2) {
    typedef boost::interprocess::allocator<int, boost::interprocess::managed_shared_memory::segment_manager> allocator_t;

    auto t1 = std::thread([] {
        auto  segment = boost::interprocess::managed_shared_memory(boost::interprocess::create_only, "MySharedMemory2", 65536);
        auto* vi      = segment.construct<std::vector<int, allocator_t>>("v")(segment.get_segment_manager());

        vi->push_back(0);
        vi->push_back(1);
        vi->push_back(2);
    });
    t1.join();

    auto t2 = std::thread([] {
        auto segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, "MySharedMemory2");
        auto it      = segment.find<std::vector<int, allocator_t>>("v");
        EXPECT_EQ(it.first->at(0), 0);
        EXPECT_EQ(it.first->at(1), 1);
        EXPECT_EQ(it.first->at(2), 2);
    });
    t2.join();

    boost::interprocess::shared_memory_object::remove("MySharedMemory2");
}

TEST(testInterprocess, caseSharedMemory3) {
    typedef std::pair<const std::string, std::string>                                                                 value_type_t;
    typedef boost::interprocess::allocator<value_type_t, boost::interprocess::managed_shared_memory::segment_manager> allocator_t;

    auto t1 = std::thread([] {
        auto  segment = boost::interprocess::managed_shared_memory(boost::interprocess::create_only, "MySharedMemory3", 65536);
        auto* m       = segment.construct<std::map<std::string, std::string, std::less<std::string>, allocator_t>>("m")(std::less<std::string>(), segment.get_segment_manager());

        m->insert(value_type_t("key0", "val0"));
        m->insert(std::pair<std::string, std::string>("key1", "val1"));
        m->insert(std::pair<std::string, std::string>("key2", "val2"));
    });
    t1.join();

    auto t2 = std::thread([] {
        auto segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, "MySharedMemory3");
        auto it      = segment.find<std::map<std::string, std::string, std::less<std::string>, allocator_t>>("m");
        EXPECT_EQ(it.first->at("key0"), "val0");
        EXPECT_EQ(it.first->at("key1"), "val1");
        EXPECT_EQ(it.first->at("key2"), "val2");
    });
    t2.join();

    boost::interprocess::shared_memory_object::remove("MySharedMemory3");
}

TEST(testInterprocess, caseMessageQueue) {
    auto mq = boost::interprocess::message_queue(boost::interprocess::create_only, "MyMessageQueue", 100, sizeof(int));

    auto t1 = std::thread([&mq] {
        for (int i = 0; i < 3; i++) {
            mq.send(&i, sizeof(i), 0);
        }
    });
    t1.join();

    auto t2 = std::thread([&mq] {
        int                                           num;
        boost::interprocess::message_queue::size_type size;
        unsigned int                                  priority;
        mq.receive(&num, sizeof(num), size, priority);
        EXPECT_EQ(num, 0);
        mq.receive(&num, sizeof(num), size, priority);
        EXPECT_EQ(num, 1);
        mq.receive(&num, sizeof(num), size, priority);
    });
    t2.join();

    boost::interprocess::message_queue::remove("MyMessageQueue");
}
