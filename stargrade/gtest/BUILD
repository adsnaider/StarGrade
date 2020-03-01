cc_library(
    name = "gradescope_test_listener",
    visibility = ['//visiblity:public'],
    srcs = ["gradescope_test_listener.cc"],
    hdrs = ["gradescope_test_listener.h"],
    linkopts = ["-l gtest"],
    deps = [
        "@abseil//absl/container:flat_hash_map",
        "@nlohmann//:json",
    ],
)

