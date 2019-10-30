#ifndef MY_CLASS_H
#define MY_CLASS_H

#include <Service.grpc.pb.h>

namespace MyLibrary
{
class MyClass : public Utilities::Connection::Service
{
public:
  explicit MyClass();
  ~MyClass();

  int sum(int a, int b);

  void runServer(std::string address);

  grpc::Status CheckTemperature(grpc::ServerContext* context, const Utilities::CheckTemperatureRequest* request, Utilities::CheckTemperatureResponse* response) override;
};
}
#endif // M_CLASS_H
