#include "stargrade/gradescope/gradescope_test_results.h"

namespace stargrade {

void to_json(nlohmann::json &j, const GradescopeTestResults &test_results) {
  j["max_score"] = test_results.config_.max_score;
  j["name"] = test_results.config_.test_name;
  j["number"] = test_results.config_.number;
  j["visibility"] = test_results.config_.visibility;
  j["tags"] = test_results.config_.tags;

  j["score"] = test_results.score_;
  j["output"] = test_results.output_;
}

}  // namespace stargrade

