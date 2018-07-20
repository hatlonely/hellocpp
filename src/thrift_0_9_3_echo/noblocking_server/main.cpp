#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <boost/make_shared.hpp>
#include <gflags/gflags.h>
#include "Service.h"

DEFINE_int64(threadNumber, 20, "thread number");
DEFINE_int64(sleepTimeMs, 30, "sleep time millseconds");

class ServiceHandler : virtual public addservice::ServiceIf {
public:
    ServiceHandler() {
    }
    
    void add(addservice::Response& response, const addservice::Request& request) {
        usleep(FLAGS_sleepTimeMs);
        response.v = request.a + request.b;
    }
};

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int port = 9090;
    
    auto threadManager = apache::thrift::concurrency::ThreadManager::newSimpleThreadManager(FLAGS_threadNumber);
    threadManager->threadFactory(boost::make_shared<apache::thrift::concurrency::PlatformThreadFactory>());
    threadManager->start();

    apache::thrift::server::TNonblockingServer server(
        boost::make_shared<addservice::ServiceProcessor>(
            boost::make_shared<ServiceHandler>()),
        boost::make_shared<::apache::thrift::protocol::TBinaryProtocolFactory>(),
        port,
        threadManager);
    server.serve();
    return 0;
}
