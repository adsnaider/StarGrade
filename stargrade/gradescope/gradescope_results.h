#ifndef STARGRADE_GRADESCOPE_GRADESCOPE_RESULTS_H_
#define STARGRADE_GRADESCOPE_GRADESCOPE_RESULTS_H_

#include <chrono>
#include <string>
#include <vector>

#include "absl/types/optional.h"
#include "yaml-cpp/yaml.h"

#include "stargrade/gradescope/gradescope_part_results.h"
#include "stargrade/gradescope/gradescope_visibility.h"

namespace stargrade {

struct GradescopeConfig {
  absl::optional<std::string> output;
  absl::optional<GradescopeVisibility> stdout_visibility;
  std::list<GradescopePartConfig> part_config;
};

class GradescopeResults {
 public:
  GradescopeResults(GradescopeConfig config);

  void ExecuteAll();
  void Emit(const std::string &json);

 private:
  std::vector<GradescopePartResults> parts_;
  GradescopeConfig config_;

  std::chrono::seconds execution_time_;

  friend void to_json(nlohmann::json &j, const GradescopeResults &);
};

}  // namespace stargrade

template <>
struct YAML::convert<stargrade::GradescopeConfig> {
  static bool decode(const Node &node, stargrade::GradescopeConfig &rhs) {
    if (!node["test_parts"]) return false;
    if (node["output"]) {
      rhs.output = node["output"].as<std::string>();
    }
    if (node["visibility"]) {
      rhs.stdout_visibility = stargrade::GradescopeVisibility::FromString(
          node["stdout_visibility"].as<std::string>());
    }
    rhs.part_config =
        node["test_parts"].as<std::list<stargrade::GradescopePartConfig>>();
    return true;
  }
};
#endif  // STARGRADE_GRADESCOPE_GRADESCOPE_RESULTS_H_
