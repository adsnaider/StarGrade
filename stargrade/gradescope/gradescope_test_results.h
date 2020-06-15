#ifndef STARGRADE_GRADESCOPE_GRADESCOPE_TEST_RESULTS_H_
#define STARGRADE_GRADESCOPE_GRADESCOPE_TEST_RESULTS_H_

#include <list>
#include <string>

#include "absl/types/optional.h"
#include "nlohmann/json.hpp"
#include "yaml-cpp/yaml.h"

#include "stargrade/gradescope/gradescope_visibility.h"

namespace stargrade {

struct GradescopeTestConfig {
  // Gradescope required
  double max_score;
  std::string test_name;
  absl::optional<std::string> number;
  absl::optional<GradescopeVisibility> visibility;
  std::list<std::string> tags;

  // Extra data.
  std::string id;
};

class GradescopeTestResults {
 public:
  GradescopeTestResults(GradescopeTestConfig config)
      : score_(0.0), config_(std::move(config)) {}

  inline void Passed(bool pass) { score_ = pass ? config_.max_score : 0; }
  inline void Output(std::string str) { output_ = std::move(str); }

 private:
  double score_;
  std::string output_;
  GradescopeTestConfig config_;

  friend void to_json(nlohmann::json &j, const GradescopeTestResults &);
};

}  // namespace stargrade

template <>
struct YAML::convert<stargrade::GradescopeTestConfig> {
  static bool decode(const Node &node, stargrade::GradescopeTestConfig &rhs) {
    if (!node["id"]) return false;
    if (!node["max_score"]) return false;
    if (!node["name"]) return false;
    rhs.id = node["id"].as<std::string>();
    rhs.max_score = node["max_score"].as<double>();
    rhs.test_name = node["name"].as<std::string>();
    if (node["number"]) {
      rhs.number = node["number"].as<std::string>();
    }
    if (node["visibility"]) {
      rhs.visibility = node["visibility"].as<std::string>();
    }
    if (node["tags"]) {
      rhs.tags = node["tags"].as<std::list<std::string>>();
    }
    return true;
  }
};

#endif  // STARGRADE_GRADESCOPE_GRADESCOPE_TEST_RESULTS_H_
