package(default_visibility = ["//visibility:public"])

cc_library(
    name = "gradescope_test_listener",
    srcs = ["gradescope_test_listener.cc"],
    hdrs = ["gradescope_test_listener.h"],
    linkopts = ["-l gtest"],
    linkstatic = True,
    deps = [
        "@nlohmann//:json",
    ],
)
