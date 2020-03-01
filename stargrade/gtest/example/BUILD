cc_binary(
    name = "example_test",
    srcs = ["example_test.cc"],
    deps = [
        ":gradescope_test_listener",
        "@abseil//absl/flags:flag",
        "@abseil//absl/flags:parse",
    ],
)

cc_binary(
    name = "runner",
    srcs = ["runner.cc"],
    deps = ["//stargrade/gradescope:gradescope_results"],
)
