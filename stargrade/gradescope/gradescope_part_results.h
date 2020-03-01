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
  std::string runfile;
  std::list<GradescopeTestConfig> tests_config;
  std::list<std::string> args;
  std::list<std::pair<std::string, std::string>> flags;
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
    rhs.runfile = node["runfile"].as<std::string>();
    if (node["args"]) {
      rhs.args = node["args"].as<std::list<std::string>>();
    }
    if (node["flags"]) {
      rhs.flags =
          node["flags"].as<std::list<std::pair<std::string, std::string>>>();
    }
    rhs.tests_config =
        node["tests"].as<std::list<stargrade::GradescopeTestConfig>>();
    return true;
  }
};

#endif  // STARGRADE_GRADESCOPE_GRADESCOPE_PART_RESULTS_H_
