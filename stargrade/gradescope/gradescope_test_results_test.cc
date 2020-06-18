#include "stargrade/gradescope/gradescope_test_results.h"

#include "gtest/gtest.h"

namespace stargrade {
namespace testing {

class GradescopeTestResultsTest : public ::testing::Test {
 protected:
  GradescopeTestResultsTest() {
    GradescopeTestConfig config;
    config.max_score = 100;
    config.test_name = "foo";
    config.visibility = GradescopeVisibility::FromString("hidden");
    config.id = "foo";
    results_ = config;
  }

  GradescopeTestResults results_;
};

TEST_F(GradescopeTestResultsTest, CorrectJsonOutput) {
  results_.Passed(true);
  results_.Output("some output");
  nlohmann::json actual = results_;

  nlohmann::json expected;
  expected["max_score"] = 100.0;
  expected["name"] = "foo";
  expected["visibility"] = "hidden";
  expected["score"] = 100.0;
  expected["output"] = "some output";

  EXPECT_EQ(actual, expected);
}

}  // namespace testing
}  // namespace stargrade
