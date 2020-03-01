package(default_visibility = ["//visibility:__pkg__"])

cc_library(
    name = "gradescope_results",
    srcs = ["gradescope_results.cc"],
    hdrs = ["gradescope_results.h"],
    deps = [
        "@abseil//absl/strings",
        "@abseil//absl/time",
        ":gradescope_part_results",
        ":gradescope_visibility",
        "@nlohmann//:json",
        "@yaml_cpp//:yaml-cpp",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "gradescope_part_results",
    srcs = ["gradescope_part_results.cc"],
    hdrs = ["gradescope_part_results.h"],
    deps = [
        ":gradescope_test_results",
        "@nlohmann//:json",
        "@yaml_cpp//:yaml-cpp",
    ],
)

cc_library(
    name = "gradescope_test_results",
    srcs = ["gradescope_test_results.cc"],
    hdrs = ["gradescope_test_results.h"],
    deps = [
        "@abseil//absl/strings",
        ":gradescope_visibility",
        "@nlohmann//:json",
        "@yaml_cpp//:yaml-cpp",
    ],
)

cc_library(
    name = "gradescope_visibility",
    hdrs = ["gradescope_visibility.h"],
    deps = [
        "@abseil//absl/strings",
    ],
)
