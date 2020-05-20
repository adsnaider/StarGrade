#ifndef STARGRADE_GRADESCOPE_GRADESCOPE_VISIBILITY_H_
#define STARGRADE_GRADESCOPE_GRADESCOPE_VISIBILITY_H_

#include <string>

#include "absl/strings/string_view.h"

namespace stargrade {

class GradescopeVisibility {
 public:
  enum VisibilityType { VISIBLE, AFTER_DUE_DATE, HIDDEN };
  GradescopeVisibility() = default;
  GradescopeVisibility(const GradescopeVisibility &) = default;
  GradescopeVisibility(GradescopeVisibility &&) noexcept = default;
  GradescopeVisibility &operator=(const GradescopeVisibility &) = default;
  GradescopeVisibility &operator=(GradescopeVisibility &&) noexcept = default;

  GradescopeVisibility(VisibilityType value);
  GradescopeVisibility &operator=(VisibilityType value);

  static GradescopeVisibility FromString(absl::string_view value);
  std::string ToString() const;

  inline VisibilityType value() const { return value_; }

 private:
  VisibilityType value_;
};

}  // namespace stargrade

#endif  // STARGRADE_GRADESCOPE_GRADESCOPE_VISIBILITY_H_
