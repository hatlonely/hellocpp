#include <gflags/gflags.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/stdcxx.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>
#include "Service.h"

DEFINE_int64(threadNumber, 100, "thread number");
DEFINE_int64(elapseTimeS, 60, "elapse seconds");
DEFINE_string(host, "127.0.0.1", "host");
DEFINE_int64(port, 9090, "port");

int nowUs() {
    timeval now = {0, 0};
    gettimeofday(&now, NULL);

    return int(now.tv_sec * 1000000 + now.tv_usec);
}

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int threadNum = FLAGS_threadNumber;
    int elapseTimeUs = FLAGS_elapseTimeS * 1000000;

    std::vector<std::thread*> vt;
    std::vector<int64_t> times(threadNum);
    std::vector<int64_t> nums(threadNum);
    auto t0 = nowUs();
    for (int i = 0; i < threadNum; i++) {
        vt.emplace_back(new std::thread([&](int idx) {
            while (true) {
                auto t1 = nowUs();
                auto socket = apache::thrift::stdcxx::make_shared<apache::thrift::transport::TSocket>(FLAGS_host, FLAGS_port);
                socket->setConnTimeout(1000);
                socket->setSendTimeout(1000);
                socket->setRecvTimeout(1000);
                auto transport = apache::thrift::stdcxx::make_shared<apache::thrift::transport::TBufferedTransport>(socket);
                auto protocol = apache::thrift::stdcxx::make_shared<apache::thrift::protocol::TBinaryProtocol>(transport);
                addservice::ServiceClient client(protocol);

                try {
                    transport->open();

                    addservice::Response response;
                    addservice::Request request;
                    request.a = 1;
                    request.b = 2;
                    client.add(response, request);

                    transport->close();
                } catch (apache::thrift::TException& tx) {
                    std::cout << "ERROR: " << tx.what() << std::endl;
                }
                auto t2 = nowUs();
                times[idx] += t2 - t1;
                nums[idx]++;
                if (t2 - t0 > elapseTimeUs) {
                    break;
                }
            }
        }, i));
    }
    for (auto t : vt) {
        if (t->joinable()) {
            t->join();
        }
    }
    auto t3 = nowUs();
    int64_t totalTime = 0;
    int64_t totalNum = 0;
    for (auto i : times) {
        totalTime += i;
    }
    for (auto i : nums) {
        totalNum += i;
    }

    std::cout << "threadNumber: " << FLAGS_threadNumber << std::endl;
    std::cout << "elapseTimeS: " << FLAGS_elapseTimeS << "s" << std::endl;
    std::cout << "RES: " << totalTime / totalNum << "us" << std::endl;
    std::cout << "QPS: " << totalNum * 1000000.0 / (t3 - t0) << std::endl;
}
