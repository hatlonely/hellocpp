#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <boost/make_shared.hpp>
#include "Service.h"

class ServiceHandler : virtual public addservice::ServiceIf {
   public:
    ServiceHandler() {
    }

    void add(addservice::Response& response, const addservice::Request& request) {
        usleep(30000);
        response.v = request.a + request.b;
    }
};

int main(int argc, const char* argv[]) {
    int port = 9090;
    int threadNumber = 20;

    auto threadManager = apache::thrift::concurrency::ThreadManager::newSimpleThreadManager(threadNumber);
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
