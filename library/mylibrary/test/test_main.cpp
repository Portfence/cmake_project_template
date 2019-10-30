#include <Service.grpc.pb.h>
#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    Utilities::CheckTemperatureRequest r;
    r.set_id(2);
    return RUN_ALL_TESTS();
}