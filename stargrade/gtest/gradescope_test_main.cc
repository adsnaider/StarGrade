#include <gtest/gtest.h>

#include "stargrade/gtest/gradescope_test_listener.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  testing::TestEventListeners &listeners =
      testing::UnitTest::GetInstance()->listeners();
  delete listeners.Release(listeners.default_result_printer());
  listeners.Append(new stargrade::GradescopeTestListener(std::cout));
  RUN_ALL_TESTS();
  return 0;
}
