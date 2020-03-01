#include "gradescope_test_listener.h"

#include <gtest/gtest.h>
#include <memory>
#include <ostream>
#include <string>

#include "nlohmann/json.hpp"

namespace stargrade {

using ::testing::TestCase;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

GradescopeTestListener::GradescopeTestListener(std::ostream &out) : out_(out) {}

void GradescopeTestListener::OnTestStart(const TestInfo &test_info) {
  current_test_name_ = std::string(test_info.test_case_name()) + "-" +
                       std::string(test_info.name());
  results_[current_test_name_].id = current_test_name_;
}

void GradescopeTestListener::OnTestPartResult(
    const TestPartResult &test_part_result) {
  if (test_part_result.failed()) {
    results_.at(current_test_name_).output +=
        std::string(test_part_result.message()) +
        std::string("\n=============\n");
  }
}

void GradescopeTestListener::OnTestEnd(const TestInfo &test_info) {
  results_[current_test_name_].passed = test_info.result()->Passed();
}

void GradescopeTestListener::OnTestProgramEnd(const UnitTest &unit_test) {
  nlohmann::json json = nlohmann::json::array();
  for (const auto &output : results_) {
    json.push_back(output.second);
  }
  out_ << json;
}

void to_json(nlohmann::json &j, const GradescopeTestOutput &test_output) {
  j["id"] = test_output.id;
  j["passed"] = test_output.passed;
  j["output"] = test_output.output;
}

}  // namespace stargrade
