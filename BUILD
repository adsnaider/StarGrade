load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")

cc_binary(
    name = "starrun",
    srcs = ["starrun.cc"],
    deps = [
        "//stargrade/gradescope:gradescope_results",
        "@abseil//absl/flags:flag",
        "@abseil//absl/flags:parse",
    ],
)

pkg_tar(
    name = "stargrade-bin",
    srcs = [":starrun"],
    mode = "0755",
    package_dir = "/usr/bin",
)

pkg_tar(
    name = "gradescope_test_listener-lib",
    srcs = [
        "//stargrade/gtest:gradescope_test_listener",
        "//stargrade/gtest:gradescope_test_main",
    ],
    mode = "0755",
    package_dir = "/usr/lib",
)

pkg_tar(
    name = "gradescope_test_listener-include",
    srcs = ["//stargrade/gtest:gradescope_test_listener.h"],
    mode = "0644",
    package_dir = "/usr/include/stargrade/gtest",
)

pkg_tar(
    name = "stargrade-data",
    extension = "tar.gz",
    deps = [
        ":gradescope_test_listener-include",
        ":gradescope_test_listener-lib",
        ":stargrade-bin",
    ],
)

pkg_deb(
    name = "stargrade-deb",
    architecture = "amd64",
    built_using = "unzip (6.0.0)",
    data = ":stargrade-data",
    depends = [
        "unzip",
    ],
    description = "foo bar",
    maintainer = "The StarGrade Authors",
    package = "stargrade-dev",
    version = "0.0.1",
)
