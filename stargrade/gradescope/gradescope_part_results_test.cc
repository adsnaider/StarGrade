#include "stargrade/gradescope/gradescope_part_results.h"

#include "glog/logging.h"
#include "gtest/gtest.h"

namespace stargrade {
namespace testing {

class GradescopePartResultsTest : public ::testing::Test {
 protected:
  GradescopePartResultsTest() {
    /*test 1*/
    GradescopeTestConfig *test = &config_.tests_config.emplace_back();
    test->max_score = 10.0;
    test->test_name = "test 1";
    test->id = "id1";

    /*test 2*/
    test = &config_.tests_config.emplace_back();
    test->max_score = 20.0;
    test->test_name = "test 2";
    test->id = "id2";

    /*test 3*/
    test = &config_.tests_config.emplace_back();
    test->max_score = 30.0;
    test->test_name = "test 3";
    test->id = "id3";
  }

  GradescopePartResults Execute(std::string run) {
    config_.run = run;
    GradescopePartResults results(config_);
    results.Execute();
    return results;
  }

 private:
  GradescopePartConfig config_;
};

TEST_F(GradescopePartResultsTest, AllPass) {
  GradescopePartResults results =
      Execute("stargrade/gradescope/testing/allpass.sh");
  nlohmann::json actual = results;

  nlohmann::json expected;

  expected[0]["max_score"] = 10.0;
  expected[0]["name"] = "test 1";
  expected[0]["score"] = 10.0;
  expected[0]["output"] = "test passed";

  expected[1]["max_score"] = 20.0;
  expected[1]["name"] = "test 2";
  expected[1]["score"] = 20.0;
  expected[1]["output"] = "test passed";

  expected[2]["max_score"] = 30.0;
  expected[2]["name"] = "test 3";
  expected[2]["score"] = 30.0;
  expected[2]["output"] = "test passed";

  EXPECT_EQ(actual, expected);
}

TEST_F(GradescopePartResultsTest, SomePass) {
  GradescopePartResults results =
      Execute("stargrade/gradescope/testing/somepass.sh");
  nlohmann::json actual = results;

  nlohmann::json expected;

  expected[0]["max_score"] = 10.0;
  expected[0]["name"] = "test 1";
  expected[0]["score"] = 10.0;
  expected[0]["output"] = "test passed";

  expected[1]["max_score"] = 20.0;
  expected[1]["name"] = "test 2";
  expected[1]["score"] = 0.0;
  expected[1]["output"] = "test failed";

  expected[2]["max_score"] = 30.0;
  expected[2]["name"] = "test 3";
  expected[2]["score"] = 30.0;
  expected[2]["output"] = "test passed";

  EXPECT_EQ(actual, expected);
}

TEST_F(GradescopePartResultsTest, NoPass) {
  GradescopePartResults results =
      Execute("stargrade/gradescope/testing/nopass.sh");
  nlohmann::json actual = results;

  nlohmann::json expected;

  expected[0]["max_score"] = 10.0;
  expected[0]["name"] = "test 1";
  expected[0]["score"] = 0.0;
  expected[0]["output"] = "test failed";

  expected[1]["max_score"] = 20.0;
  expected[1]["name"] = "test 2";
  expected[1]["score"] = 0.0;
  expected[1]["output"] = "test failed";

  expected[2]["max_score"] = 30.0;
  expected[2]["name"] = "test 3";
  expected[2]["score"] = 0.0;
  expected[2]["output"] = "test failed";

  EXPECT_EQ(actual, expected);
}

TEST_F(GradescopePartResultsTest, Invalid) {
  EXPECT_ANY_THROW(Execute("stargrade/gradescope/testing/invalid.sh"));
}
}  // namespace testing
}  // namespace stargrade
