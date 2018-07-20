#include <gflags/gflags.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include "Service.h"

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
        auto sock = apache::thrift::stdcxx::dynamic_pointer_cast<apache::thrift::transport::TSocket>(connInfo.transport);
        return new ServiceHandler(sock->getPeerAddress());
    }
    virtual void releaseHandler(addservice::ServiceIf* handler) {
        delete handler;
    }
};

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    int port = 9090;
    apache::thrift::server::TThreadedServer server(
        apache::thrift::stdcxx::make_shared<addservice::ServiceProcessorFactory>(
            apache::thrift::stdcxx::make_shared<ServiceCloneFactory>()),
        apache::thrift::stdcxx::make_shared<apache::thrift::transport::TServerSocket>(port),
        apache::thrift::stdcxx::make_shared<apache::thrift::transport::TBufferedTransportFactory>(),
        apache::thrift::stdcxx::make_shared<::apache::thrift::protocol::TBinaryProtocolFactory>());
    server.serve();
    return 0;
}
