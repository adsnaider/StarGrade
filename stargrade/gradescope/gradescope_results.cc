#include "stargrade/gradescope/gradescope_results.h"

#include <chrono>
#include <fstream>
#include <string>

#include "nlohmann/json.hpp"

namespace stargrade {

GradescopeResults::GradescopeResults(GradescopeConfig config)
    : config_(std::move(config)) {
  for (GradescopePartConfig &part : config_.part_config) {
    parts_.emplace_back(std::move(part));
  }
}

void GradescopeResults::ExecuteAll() {
  std::chrono::steady_clock::time_point start =
      std::chrono::steady_clock::now();
  for (GradescopePartResults &part : parts_) {
    part.Execute();
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  execution_time_ =
      std::chrono::duration_cast<std::chrono::seconds>(end - start);
}

void GradescopeResults::Emit(const std::string &json) {
  std::ofstream out(json.data());
  nlohmann::json j = *this;
  out << j;
}

void to_json(nlohmann::json &j, const GradescopeResults &gradescope_results) {
  // nlohmann::json parts = gradescope_results.parts_;
  j["execution_time"] = gradescope_results.execution_time_.count();
  if (gradescope_results.config_.output) {
    j["output"] = gradescope_results.config_.output.value();
  }
  if (gradescope_results.config_.stdout_visibility) {
    j["stdout_visibility"] =
        gradescope_results.config_.stdout_visibility.value();
  }
  nlohmann::json parts = gradescope_results.parts_;
  j["tests"] = nlohmann::json::array();
  for (const auto &part : parts) {
    j["tests"].insert(j["tests"].end(), part.begin(), part.end());
  }
}

}  // namespace stargrade
