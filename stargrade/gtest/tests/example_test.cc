#include <gtest/gtest.h>
#include <iostream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "stargrade/gtest/gradescope_test_listener.h"

ABSL_FLAG(bool, gradescope, false,
          "Defines whether to output the results for Gradescope or not.");

TEST(Foobar, Foo) {
  EXPECT_TRUE(false);
  EXPECT_EQ(2, 3);
  EXPECT_EQ("foo", "foo");
}

TEST(Foobar, Bar) { EXPECT_EQ("foo", "foo"); }

int main(int argc, char **argv) {
  absl::ParseCommandLine(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  if (absl::GetFlag(FLAGS_gradescope)) {
    std::cerr << "HERE";
    testing::TestEventListeners &listeners =
        testing::UnitTest::GetInstance()->listeners();
    delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new stargrade::GradescopeTestListener(std::cout));
    std::cerr << "HERE2";
    RUN_ALL_TESTS();
    std::cerr << "HERE3";
    return 0;
  } else {
    return RUN_ALL_TESTS();
  }
}
