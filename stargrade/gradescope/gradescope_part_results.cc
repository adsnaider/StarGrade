#include "stargrade/gradescope/gradescope_part_results.h"

#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>

#include "nlohmann/json.hpp"

namespace stargrade {

namespace {
constexpr size_t BUFFER_SIZE = 512;

}  // namespace

GradescopePartResults::GradescopePartResults(GradescopePartConfig config)
    : config_(std::move(config)) {
  for (GradescopeTestConfig &config : config_.tests_config) {
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
      GradescopePartOutput part_output = nlohmann::json::parse(test_result);
      for (const auto &test_output : part_output) {
        if (tests_.count(test_output.id) == 0) {
          // TODO: log something
          continue;
        }
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
    if (config_.run) {
      std::istringstream s(config_.run.value());
      std::vector<std::string> tokens;
      std::string val;
      while (s >> val) {
        tokens.push_back(val);
      }
      char **argv = new char *[tokens.size() + 1];
      for (int i = 0; i < tokens.size(); ++i) {
        argv[i] = new char[tokens[i].size() + 1];
        strncpy(argv[i], tokens[i].c_str(), tokens[i].size() + 1);
      }
      argv[tokens.size()] = nullptr;
      execvp(argv[0], argv);
    } else if (config_.sh) {
      execlp("/bin/sh/", "/bin/sh/", "-c", config_.sh->c_str());
    }
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
