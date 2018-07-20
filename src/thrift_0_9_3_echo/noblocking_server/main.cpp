#include <gflags/gflags.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <boost/make_shared.hpp>
#include "Service.h"

DEFINE_int64(threadNumber, 20, "thread number");
DEFINE_int64(sleepTimeMs, 30, "sleep time millseconds");

class ServiceHandler : virtual public addservice::ServiceIf {
private:
    std::string address;
public:
    ServiceHandler(std::string address) {
        this->address = address;
    }
    
    void add(addservice::Response& response, const addservice::Request& request) {
        usleep(FLAGS_sleepTimeMs * 1000);
        response.v = request.a + request.b;
    }
};

class ServiceCloneFactory : virtual public addservice::ServiceIfFactory {
public:
    virtual ~ServiceCloneFactory() {}
    virtual addservice::ServiceIf* getHandler(const apache::thrift::TConnectionInfo& connInfo) {
        auto sock = boost::dynamic_pointer_cast<apache::thrift::transport::TSocket>(connInfo.transport);
        return new ServiceHandler(sock->getPeerAddress());
    }
    virtual void releaseHandler(addservice::ServiceIf* handler) {
        delete handler;
    }
};

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int port = 9090;

    auto threadManager = apache::thrift::concurrency::ThreadManager::newSimpleThreadManager(FLAGS_threadNumber);
    threadManager->threadFactory(boost::make_shared<apache::thrift::concurrency::PlatformThreadFactory>());
    threadManager->start();

    apache::thrift::server::TNonblockingServer server(
        boost::make_shared<addservice::ServiceProcessorFactory>(
            boost::make_shared<ServiceCloneFactory>()),
        boost::make_shared<::apache::thrift::protocol::TBinaryProtocolFactory>(),
        port,
        threadManager);
    server.serve();
    return 0;
}
