#include "mylibrary/my_class.h"

#include <grpcpp/grpcpp.h>
#include <google/protobuf/util/message_differencer.h>
#include <experimental/filesystem>
#include <Service.grpc.pb.h>

namespace MyLibrary
{
MyClass::MyClass()
{
}

MyClass::~MyClass()
{

}

int MyClass::sum(int a, int b)
{
  std::experimental::filesystem::exists("Log");
  grpc::Status status = grpc::Status(grpc::StatusCode::OK, "Works");
  return a + b;
}

grpc::Status MyClass::CheckTemperature(grpc::ServerContext* context, const Utilities::CheckTemperatureRequest* request, Utilities::CheckTemperatureResponse* response)
{
  grpc::Status status(grpc::StatusCode::OK, "RPC OK");
  return status;
}

void MyClass::runServer(std::string address)
{
  grpc::ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(this);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << address << std::endl;
  server->Wait();
}
} // namespace MyLibrary