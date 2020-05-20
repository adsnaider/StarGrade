package(default_visibility = ["//visibility:__pkg__"])

cc_library(
    name = "gradescope_results",
    srcs = ["gradescope_results.cc"],
    hdrs = ["gradescope_results.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":gradescope_part_results",
        ":gradescope_visibility",
        "@abseil//absl/types:optional",
        "@nlohmann//:json",
        "@yaml_cpp//:yaml-cpp",
    ],
)

cc_test(
    name = "gradescope_results_test",
    size = "small",
    srcs = ["gradescope_results_test.cc"],
    data = [
        "testing/allpass.sh",
        "testing/config.yaml",
        "testing/invalid.sh",
        "testing/nopass.sh",
        "testing/somepass.sh",
    ],
    deps = [
        ":gradescope_results",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "gradescope_part_results",
    srcs = ["gradescope_part_results.cc"],
    hdrs = ["gradescope_part_results.h"],
    deps = [
        ":gradescope_test_results",
        "@glog",
        "@nlohmann//:json",
        "@yaml_cpp//:yaml-cpp",
    ],
)

cc_test(
    name = "gradescope_part_results_test",
    size = "small",
    srcs = ["gradescope_part_results_test.cc"],
    data = [
        "testing/allpass.sh",
        "testing/invalid.sh",
        "testing/nopass.sh",
        "testing/somepass.sh",
    ],
    deps = [
        ":gradescope_part_results",
        "@abseil//absl/strings",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "gradescope_test_results",
    srcs = ["gradescope_test_results.cc"],
    hdrs = ["gradescope_test_results.h"],
    deps = [
        ":gradescope_visibility",
        "@abseil//absl/types:optional",
        "@nlohmann//:json",
        "@yaml_cpp//:yaml-cpp",
    ],
)

cc_test(
    name = "gradescope_test_results_test",
    size = "small",
    srcs = ["gradescope_test_results_test.cc"],
    deps = [
        ":gradescope_test_results",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "gradescope_visibility",
    srcs = ["gradescope_visibility.cc"],
    hdrs = ["gradescope_visibility.h"],
    deps = ["@abseil//absl/strings"],
)

cc_test(
    name = "gradescope_visibility_test",
    size = "small",
    srcs = ["gradescope_visibility_test.cc"],
    deps = [
        ":gradescope_visibility",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
