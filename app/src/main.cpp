#include <iostream>
#include <gen/Service.grpc.pb.h>
#include <mylibrary/my_class.h>
#include <boost/regex.hpp>
#include <boost/log/trivial.hpp>
#include <grpcpp/grpcpp.h>
#include <optional>

#include <experimental/filesystem>

using std::experimental::filesystem::directory_iterator;

int main()
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  MyLibrary::MyClass myClass;
  grpc::Status ok;
  std::cout << "Sum: 2+3=" << myClass.sum(2,3) << std::endl;
  std::vector<bool> v(10);
  for (const auto&& e : v)
  {
    std::cout << e <<std::endl;
  }
  return 0;
}