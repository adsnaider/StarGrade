load("@rules_pkg//:pkg.bzl", "pkg_deb", "pkg_tar")
load("@com_github_google_rules_install//installer:def.bzl", "installer")

installer(
    name = "install_starrun",
    data = [":starrun"],
    executable = True,
)

installer(
    name = "install_stargrade_gtest",
    data = [
        "//stargrade/gtest:gradescope_test_listener",
        "//stargrade/gtest:gradescope_test_main",
    ],
    executable = False,
)

installer(
    name = "install_stargrade_gtest_headers",
    data = ["//stargrade/gtest:gradescope_test_listener.h"],
    executable = False,
)

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
