#include "stargrade/gradescope/gradescope_results.h"

#include <unistd.h>
#include <iostream>

int main() {
  stargrade::GradescopeConfig config =
      YAML::LoadFile("example.yaml").as<stargrade::GradescopeConfig>();
  stargrade::GradescopeResults results(config);
  results.ExecuteAll();
  results.Emit("out.json");
}
