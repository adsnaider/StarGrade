#include "stargrade/gradescope/gradescope_part.grpc.pb.h"

namespace stargrade {

class TesterServiceImpl final : public proto::Tester::Service {
  grpc::Status LogTest(grpc::ServerContext *context,
                       const proto::LogTestRequest *request,
                       proto::LogTestResponse *response) override {
    return grpc::Status::OK;
  }
};

}  // namespace stargrade
