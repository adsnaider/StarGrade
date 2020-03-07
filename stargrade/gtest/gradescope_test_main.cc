#include <gtest/gtest.h>

#ifdef GRADESCOPE_TEST
#include <stargrade/gtest/gradescope_test_listener.h>
#endif

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef GRADESCOPE_TEST
  testing::TestEventListeners &listeners =
      testing::UnitTest::GetInstance()->listeners();
  delete listeners.Release(listeners.default_result_printer());
  listeners.Append(new stargrade::GradescopeTestListener(std::cout));
  RUN_ALL_TESTS();
  return 0;
#else
  return RUN_ALL_TESTS();
#endif  // GRADESCOPE_TEST
}
