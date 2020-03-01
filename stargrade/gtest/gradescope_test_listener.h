#ifndef STARGRADE_GTEST_GRADESCOPE_TEST_LISTENER_H_
#define STARGRADE_GTEST_GRADESCOPE_TEST_LISTENER_H_

#include <gtest/gtest.h>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>

#include "nlohmann/json.hpp"

namespace stargrade {

// TODO: Figure out if there's a way to include the structure from
// gradescope_part_results.h
struct GradescopeTestOutput {
  std::string id;
  bool passed;
  std::string output;
};

void to_json(nlohmann::json &j, const GradescopeTestOutput &test_output);

class GradescopeTestListener : public ::testing::EmptyTestEventListener {
 public:
  GradescopeTestListener(std::ostream &out);

 private:
  virtual void OnTestStart(const testing::TestInfo & /*test_info*/) override;
  virtual void OnTestPartResult(
      const testing::TestPartResult & /*test_part_result*/) override;
  virtual void OnTestEnd(const testing::TestInfo & /*test_info*/) override;
  virtual void OnTestProgramEnd(
      const testing::UnitTest & /*unit_test*/) override;

  std::ostream &out_;
  std::unordered_map<std::string, GradescopeTestOutput> results_;

  std::string current_test_name_;
};
}  // namespace stargrade

#endif  // STARGRADE_GTEST_GRADESCOPE_TEST_LISTENER_H_
