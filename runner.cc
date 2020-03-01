#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include "stargrade/gradescope/gradescope_results.h"

ABSL_FLAG(std::string, results, "",
          "Path to which in which to save the results.json output.");
ABSL_FLAG(std::string, config, "", "Configuration file.");

int main(int argc, char **argv) {
  absl::ParseCommandLine(argc, argv);
  stargrade::GradescopeConfig config =
      YAML::LoadFile(absl::GetFlag(FLAGS_config))
          .as<stargrade::GradescopeConfig>();
  stargrade::GradescopeResults results(config);
  results.ExecuteAll();
  results.Emit(absl::GetFlag(FLAGS_results));
}
