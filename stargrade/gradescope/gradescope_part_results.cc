#include "stargrade/gradescope/gradescope_part_results.h"

#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cmath>
#include <cstring>
#include <iostream>

#include "absl/strings/str_join.h"
#include "nlohmann/json.hpp"

namespace stargrade {

namespace {
constexpr size_t BUFFER_SIZE = 512;

}  // namespace

GradescopePartResults::GradescopePartResults(GradescopePartConfig config)
    : config_(std::move(config)) {
  for (GradescopeTestConfig &config : config_.tests_config) {
    std::cout << "Test result ID: " << config.id << std::endl;
    tests_.emplace(std::make_pair(config.id, std::move(config)));
  }
}

void GradescopePartResults::Execute() {
  // Fork exec, pipe, permissions, read, decode. Set tests.

  // Create file descriptors for pipe.
  int fd[2];
  pipe(fd);
  if (fork() != 0) {
    // i.e. current process
    close(fd[1]);  // We don't need fd's output.
    int ifd = fd[0];
    int status;
    // TODO: Timeout?
    wait(&status);
    // Error status?
    if (status == 0) {
      // Execution of subprocess went well. Test's output should be in ifd.
      std::string test_result;
      // Read blocks of BUFFER_SIZE bytes at a time.
      char buffer[BUFFER_SIZE];
      for (int count = read(ifd, buffer, BUFFER_SIZE); count > 0;
           count = read(ifd, buffer, BUFFER_SIZE)) {
        test_result.append(buffer, count);
      }
      // TODO: Deserialize
      std::cerr << test_result << std::endl;
      GradescopePartOutput part_output = nlohmann::json::parse(test_result);
      for (const auto &test_output : part_output) {
        tests_.at(test_output.id).Passed(test_output.passed);
        tests_.at(test_output.id).Output(test_output.output);
      }
    } else {
      std::cerr << "Failure in tests.\n";
    }
  } else {
    // i.e. new "test" process.
    close(fd[0]);  // We don't need fd's input.
    int ofd = fd[1];
    dup2(ofd, /*STD_OUTPUT*/ 1);
    // TODO: permissions?
    // Two extra spaces for execution name and nullptr.
    char **argv = new char *[config_.args.size() + config_.flags.size() + 2];
    int i = 0;
    argv[i] = new char[config_.runfile.size() + 1];
    strncpy(argv[i++], config_.runfile.c_str(), config_.runfile.size() + 1);
    for (const std::string &arg : config_.args) {
      argv[i] = new char[arg.size() + 1];
      strncpy(argv[i++], arg.c_str(), arg.size() + 1);
    }

    for (const auto &flag : config_.flags) {
      std::string arg =
          absl::StrCat("--", absl::StrJoin({flag.first, flag.second}, "="));
      argv[i] = new char[arg.size() + 1];
      strncpy(argv[i++], arg.c_str(), arg.size() + 1);
    }
    argv[i] = nullptr;
    std::cerr << "Running: " << config_.runfile.c_str() << std::endl;
    std::cerr << "Arg #1: " << argv[0] << std::endl;
    std::cerr << "Arg #2: " << argv[1] << std::endl;
    execvp(config_.runfile.c_str(), argv);
  }
}

void from_json(const nlohmann::json &j, GradescopeTestOutput &test_output) {
  j.at("id").get_to(test_output.id);
  j.at("passed").get_to(test_output.passed);
  j.at("output").get_to(test_output.output);
}

void to_json(nlohmann::json &j, const GradescopePartResults &part_results) {
  // Lists of tests.
  j = nlohmann::json::array();
  for (const auto &test_pair : part_results.tests_) {
    j.push_back(test_pair.second);
  }
}

}  // namespace stargrade
