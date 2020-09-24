package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gradescope_test_listener",
    srcs = ["gradescope_test_listener.cc"],
    hdrs = ["gradescope_test_listener.h"],
    linkopts = ["-l gtest"],
    deps = [
        "@nlohmann//:json",
    ],
)

cc_library(
    name = "gradescope_test_main",
    srcs = ["gradescope_test_main.cc"],
    linkopts = [
        "-l gtest",
        "-l pthread",
    ],
    deps = [":gradescope_test_listener"],
)
