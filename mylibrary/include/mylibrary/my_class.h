#ifndef MY_CLASS_H
#define MY_CLASS_H

#include <myproto/service.grpc.pb.h>

namespace MyLibrary
{
class MyClass : public registration::Registration::Service
{
public:
  explicit MyClass() = default;
  ~MyClass() = default;

  int sum(int a, int b);

  void runServer(std::string address);

  grpc::Status RegisterService(grpc::ServerContext* context, const registration::RegisterServiceRequest* request, registration::RegisterServiceResponse* response) override;
};
}
#endif // M_CLASS_H
