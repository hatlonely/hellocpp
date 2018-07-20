#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include "Service.h"

class ServiceHandler : virtual public addservice::ServiceIf {
   public:
    ServiceHandler() {
    }

    void add(addservice::Response& response, const addservice::Request& request) {
        usleep(30);
        response.v = request.a + request.b;
    }
};

int main(int argc, const char* argv[]) {
    int port = 9090;
    apache::thrift::server::TSimpleServer server(
        ::apache::thrift::stdcxx::make_shared<addservice::ServiceProcessor>(
            ::apache::thrift::stdcxx::make_shared<ServiceHandler>()),
        ::apache::thrift::stdcxx::make_shared<apache::thrift::transport::TServerSocket>(port),
        ::apache::thrift::stdcxx::make_shared<apache::thrift::transport::TBufferedTransportFactory>(),
        ::apache::thrift::stdcxx::make_shared<::apache::thrift::protocol::TBinaryProtocolFactory>());
    server.serve();
    return 0;
}
