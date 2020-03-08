#ifndef STARGRADE_GRADESCOPE_GRADESCOPE_PART_RESULTS_H_
#define STARGRADE_GRADESCOPE_GRADESCOPE_PART_RESULTS_H_

#include <map>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"
#include "yaml-cpp/yaml.h"

#include "stargrade/gradescope/gradescope_test_results.h"

namespace stargrade {

struct GradescopePartConfig {
  std::string run;
  std::vector<GradescopeTestConfig> tests_config;
};

class GradescopePartResults {
 public:
  GradescopePartResults(GradescopePartConfig config);
  void Execute();

 private:
  GradescopePartConfig config_;
  std::map<std::string, GradescopeTestResults> tests_;

  friend void to_json(nlohmann::json &j, const GradescopePartResults &);
};

struct GradescopeTestOutput {
  std::string id;
  bool passed;
  std::string output;
};

void from_json(const nlohmann::json &j, GradescopeTestOutput &test_output);

typedef std::vector<GradescopeTestOutput> GradescopePartOutput;

}  // namespace stargrade

template <>
struct YAML::convert<stargrade::GradescopePartConfig> {
  static bool decode(const Node &node, stargrade::GradescopePartConfig &rhs) {
    if (!node["run"]) return false;
    if (!node["tests"]) return false;
    rhs.run = node["run"].as<std::string>();
    rhs.tests_config =
        node["tests"].as<std::vector<stargrade::GradescopeTestConfig>>();
    return true;
  }
};

#endif  // STARGRADE_GRADESCOPE_GRADESCOPE_PART_RESULTS_H_
