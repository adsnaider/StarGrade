#ifndef STARGRADE_GRADESCOPE_GRADESCOPE_RESULTS_H_
#define STARGRADE_GRADESCOPE_GRADESCOPE_RESULTS_H_

#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "yaml-cpp/yaml.h"

#include "stargrade/gradescope/gradescope_part_results.h"
#include "stargrade/gradescope/gradescope_visibility.h"

namespace stargrade {

struct GradescopeConfig {
  std::string output;
  GradescopeVisibility stdout_visibility;
  std::list<GradescopePartConfig> part_config;
};

class GradescopeResults {
 public:
  GradescopeResults(GradescopeConfig config);

  void ExecuteAll();
  void Emit(absl::string_view json);

 private:
  std::vector<GradescopePartResults> parts_;
  GradescopeConfig config_;

  absl::Duration execution_time_;

  friend void to_json(nlohmann::json &j, const GradescopeResults &);
};

}  // namespace stargrade

template <>
struct YAML::convert<stargrade::GradescopeConfig> {
  static bool decode(const Node &node, stargrade::GradescopeConfig &rhs) {
    rhs.output = node["output"].as<std::string>();
    rhs.stdout_visibility = node["stdout_visibility"].as<std::string>();
    rhs.part_config =
        node["test_parts"].as<std::list<stargrade::GradescopePartConfig>>();
    return true;
  }
};
#endif  // STARGRADE_GRADESCOPE_GRADESCOPE_RESULTS_H_
