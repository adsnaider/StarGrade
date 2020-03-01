cc_library(
    name = "gradescope_test_listener",
    srcs = ["gradescope_test_listener.cc"],
    hdrs = ["gradescope_test_listener.h"],
    linkopts = ["-l gtest"],
    visibility = ["//visibility:public"],
    deps = [
        "@abseil//absl/strings",
        "@nlohmann//:json",
    ],
)
