#include "stargrade/gradescope/gradescope_visibility.h"

namespace stargrade {

GradescopeVisibility::GradescopeVisibility(VisibilityType value)
    : value_(value) {}
GradescopeVisibility &GradescopeVisibility::operator=(VisibilityType value) {
  value_ = value;
  return *this;
}

// static
GradescopeVisibility GradescopeVisibility::FromString(absl::string_view value) {
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

std::string GradescopeVisibility::ToString() const {
  switch (value_) {
    case VISIBLE:
      return "visible";
    case AFTER_DUE_DATE:
      return "after_due_date";
    case HIDDEN:
      return "hidden";
    default:
      throw "Invalid visibility type.";
  }
}
}  // namespace stargrade
