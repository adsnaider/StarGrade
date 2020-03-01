#ifndef STARGRADE_GRADESCOPE_GRADESCOPE_VISIBILITY_H_
#define STARGRADE_GRADESCOPE_GRADESCOPE_VISIBILITY_H_

#include <string>

namespace stargrade {

class GradescopeVisibility {
 public:
  enum VisibilityType { VISIBLE, AFTER_DUE_DATE, HIDDEN };
  GradescopeVisibility() = default;
  GradescopeVisibility(VisibilityType value) : value_(value) {}

  explicit GradescopeVisibility(const std::string &value)
      : value_(FromString(value)) {}

  GradescopeVisibility &operator=(VisibilityType value) {
    value_ = value;
    return *this;
  }

  GradescopeVisibility &operator=(const std::string &value) {
    value_ = FromString(value);
    return *this;
  }

  explicit operator std::string() const { return ToString(value_); }

 private:
  VisibilityType value_;

  static VisibilityType FromString(const std::string &value) {
    if (value == "visible") {
      return VISIBLE;
    } else if (value == "after_due_date") {
      return AFTER_DUE_DATE;
    } else if (value == "hidden") {
      return HIDDEN;
    } else {
      throw "Invalid visibility string.";
    }
  }

  static std::string ToString(VisibilityType value) {
    switch (value) {
      case GradescopeVisibility::VISIBLE:
        return "visible";
      case GradescopeVisibility::AFTER_DUE_DATE:
        return "after_due_date";
      case GradescopeVisibility::HIDDEN:
        return "hidden";
      default:
        throw "Invalid visibility type.";
    }
  }
};

}  // namespace stargrade

#endif  // STARGRADE_GRADESCOPE_GRADESCOPE_VISIBILITY_H_
