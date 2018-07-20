#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/stdcxx.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>
#include "Service.h"

int nowUs() {
    timeval now = {0, 0};
    gettimeofday(&now, NULL);

    return int(now.tv_sec * 1000000 + now.tv_usec);
}

int main(int argc, const char* argv[]) {
    int threadNum = 1;
    int requestNum = 100;

    std::vector<std::thread*> vt;
    std::vector<int> times(threadNum);
    for (int i = 0; i < threadNum; i++) {
        vt.emplace_back(new std::thread([&](int idx) {
            for (int j = 0; j < requestNum; j++) {
                auto t1 = nowUs();
                auto socket = apache::thrift::stdcxx::make_shared<apache::thrift::transport::TSocket>("127.0.0.1", 9090);
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
            }
        }, i));
    }
    for (auto t : vt) {
        if (t->joinable()) {
            t->join();
        }
    }
    int totalTime = 0;
    for (auto i : times) {
        totalTime += i;
    }

    std::cout << totalTime / threadNum / requestNum << std::endl;
}
