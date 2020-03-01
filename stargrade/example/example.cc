#include <iostream>

int main(int argc, char **argv) {
  std::cerr << argc << std::endl;
  for (int i = 0; i < argc; ++i) {
    std::cerr << argv[i] << std::endl;
  }
  std::cout <<
      R"([{
          "id": "TestID",
          "passed": true,
          "output": "Success"
        }])";
  return 0;
}
