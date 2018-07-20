#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <boost/make_shared.hpp>
#include <gflags/gflags.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>
#include "Service.h"

DEFINE_int64(threadNumber, 10, "thread number");
DEFINE_int64(requestNumber, 1000, "request number");

int nowUs() {
    timeval now = {0, 0};
    gettimeofday(&now, NULL);

    return int(now.tv_sec * 1000000 + now.tv_usec);
}

int main(int argc, const char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int threadNum = FLAGS_threadNumber;
    int requestNum = FLAGS_requestNumber;

    std::vector<std::thread*> vt;
    std::vector<int> times(threadNum);
    auto t1 = nowUs();
    for (int i = 0; i < threadNum; i++) {
        vt.emplace_back(new std::thread([&](int idx) {
            for (int j = 0; j < requestNum; j++) {
                auto t1 = nowUs();
                auto socket = boost::make_shared<apache::thrift::transport::TSocket>("127.0.0.1", 9090);
                socket->setConnTimeout(1000);
                socket->setSendTimeout(1000);
                socket->setRecvTimeout(1000);
                auto transport = boost::make_shared<apache::thrift::transport::TBufferedTransport>(socket);
                auto protocol = boost::make_shared<apache::thrift::protocol::TBinaryProtocol>(transport);
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
            }
        }, i));
    }
    for (auto t : vt) {
        if (t->joinable()) {
            t->join();
        }
    }
    auto t2 = nowUs();
    int totalTime = 0;
    for (auto i : times) {
        totalTime += i;
    }

    std::cout << "RES: " << totalTime / threadNum / requestNum << "us" << std::endl;
    std::cout << "QPS: " << threadNum * requestNum * 1000000 / (t2 - t1) << std::endl;
}
