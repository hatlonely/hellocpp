#include <gflags/gflags.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <boost/make_shared.hpp>
#include "Service.h"

DEFINE_int64(threadNumber, 20, "thread number");
DEFINE_int64(sleepTimeMs, 30, "sleep time millseconds");

class ServiceHandler : virtual public addservice::ServiceIf {
   public:
    ServiceHandler() {
    }

    void add(addservice::Response& response, const addservice::Request& request) {
        usleep(FLAGS_sleepTimeMs * 1000);
        response.v = request.a + request.b;
    }
};

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int port = 9090;

    auto threadManager = apache::thrift::concurrency::ThreadManager::newSimpleThreadManager(FLAGS_threadNumber);
    threadManager->threadFactory(boost::make_shared<apache::thrift::concurrency::PlatformThreadFactory>());
    threadManager->start();

    apache::thrift::server::TThreadPoolServer server(
        boost::make_shared<addservice::ServiceProcessor>(
            boost::make_shared<ServiceHandler>()),
        boost::make_shared<apache::thrift::transport::TServerSocket>(port),
        boost::make_shared<apache::thrift::transport::TBufferedTransportFactory>(),
        boost::make_shared<::apache::thrift::protocol::TBinaryProtocolFactory>(),
        threadManager);
    server.serve();
    return 0;
}
