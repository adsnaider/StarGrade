#include "stargrade/gradescope/gradescope_results.h"

#include "gtest/gtest.h"

namespace stargrade {
namespace testing {

TEST(GradescopeResultsTest, FullIntegration) {
  GradescopeConfig config =
      YAML::LoadFile("stargrade/gradescope/testing/config.yaml")
          .as<stargrade::GradescopeConfig>();

  GradescopeResults results(std::move(config));

  results.ExecuteAll();
  nlohmann::json actual = results;

  nlohmann::json expected = {{"output", "Wonderful gradescope"},
                             {"tests",
                              {
                                  {{"max_score", 10.0},
                                   {"name", "test 1"},
                                   {"output", "test passed"},
                                   {"score", 10.0},
                                   {"visibility", "hidden"}},
                                  {{"max_score", 20.0},
                                   {"name", "test 2"},
                                   {"output", "test passed"},
                                   {"score", 20.0},
                                   {"visibility", "visible"}},
                                  {{"max_score", 30.0},
                                   {"name", "test 3"},
                                   {"output", "test passed"},
                                   {"score", 30.0},
                                   {"visibility", "visible"}},

                                  {{"max_score", 10.0},
                                   {"name", "test 1"},
                                   {"output", "test passed"},
                                   {"score", 10.0},
                                   {"visibility", "hidden"}},
                                  {{"max_score", 20.0},
                                   {"name", "test 2"},
                                   {"output", "test failed"},
                                   {"score", 0.0},
                                   {"visibility", "visible"}},
                                  {{"max_score", 30.0},
                                   {"name", "test 3"},
                                   {"output", "test passed"},
                                   {"score", 30.0},
                                   {"visibility", "visible"}},

                                  {{"max_score", 10.0},
                                   {"name", "test 1"},
                                   {"output", "test failed"},
                                   {"score", 0.0},
                                   {"visibility", "hidden"}},
                                  {{"max_score", 20.0},
                                   {"name", "test 2"},
                                   {"output", "test failed"},
                                   {"score", 0.0},
                                   {"visibility", "visible"}},
                                  {{"max_score", 30.0},
                                   {"name", "test 3"},
                                   {"output", "test failed"},
                                   {"score", 0.0},
                                   {"visibility", "visible"}},

                              }}};

  EXPECT_EQ(actual["tests"], expected["tests"]);
  EXPECT_EQ(actual["output"], expected["output"]);
}
}  // namespace testing
}  // namespace stargrade
