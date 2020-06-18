#include "stargrade/gradescope/gradescope_visibility.h"

#include "gtest/gtest.h"

namespace stargrade {
namespace testing {

TEST(GradescopeVisibility, FromString) {
  GradescopeVisibility visibility = GradescopeVisibility::FromString("visible");
  EXPECT_EQ(visibility.value(), GradescopeVisibility::VISIBLE);
  visibility = GradescopeVisibility::FromString("after_due_date");
  EXPECT_EQ(visibility.value(), GradescopeVisibility::AFTER_DUE_DATE);
  visibility = GradescopeVisibility::FromString("hidden");
  EXPECT_EQ(visibility.value(), GradescopeVisibility::HIDDEN);
  EXPECT_ANY_THROW(GradescopeVisibility::FromString("foo"));
}

TEST(GradescopeVisibility, ToString) {
  GradescopeVisibility visibility(GradescopeVisibility::VISIBLE);
  EXPECT_EQ(visibility.ToString(), "visible");
  visibility = GradescopeVisibility::AFTER_DUE_DATE;
  EXPECT_EQ(visibility.ToString(), "after_due_date");
  visibility = GradescopeVisibility::HIDDEN;
  EXPECT_EQ(visibility.ToString(), "hidden");
}

}  // namespace testing
}  // namespace stargrade
