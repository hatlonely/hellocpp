#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
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
    apache::thrift::server::TThreadedServer server(
        boost::make_shared<addservice::ServiceProcessor>(
            boost::make_shared<ServiceHandler>()),
        boost::make_shared<apache::thrift::transport::TServerSocket>(port),
        boost::make_shared<apache::thrift::transport::TBufferedTransportFactory>(),
        boost::make_shared<::apache::thrift::protocol::TBinaryProtocolFactory>());
    server.serve();
    return 0;
}
