workspace(name = "StarGrade")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "yaml_cpp",
    commit = "de8253fcb075c049c4ad1c466c504bf3cf022f45",
    remote = "https://github.com/jbeder/yaml-cpp.git",
)

git_repository(
    name = "abseil",
    branch = "master",
    remote = "https://github.com/abseil/abseil-cpp.git",
)

new_git_repository(
    name = "nlohmann",
    build_file = "@//third_party/rules:BUILD.nlohmann",
    remote = "https://github.com/nlohmann/json.git",
    tag = "v3.7.3",
)

git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest.git",
    tag = "release-1.10.0",
)

http_archive(
    name = "rules_pkg",
    sha256 = "4ba8f4ab0ff85f2484287ab06c0d871dcb31cc54d439457d28fd4ae14b18450a",
    url = "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.4/rules_pkg-0.2.4.tar.gz",
)

git_repository(
    name = "glog",
    remote = "https://github.com/google/glog.git",
    tag = "v0.4.0",
)

http_archive(
    name = "com_github_gflags_gflags",
    strip_prefix = "gflags-2.2.2",
    urls = [
        "https://mirror.bazel.build/github.com/gflags/gflags/archive/v2.2.2.tar.gz",
        "https://github.com/gflags/gflags/archive/v2.2.2.tar.gz",
    ],
)

http_archive(
    name = "com_github_google_rules_install",
    sha256 = "ac2c9c53aa022a110273c0e510d191a4c04c6adafefa069a5eeaa16313edc9b9",
    strip_prefix = "bazel_rules_install-0.4",
    urls = ["https://github.com/google/bazel_rules_install/releases/download/0.4/bazel_rules_install-0.4.tar.gz"],
)

load("@com_github_google_rules_install//:deps.bzl", "install_rules_dependencies")

install_rules_dependencies()

load("@com_github_google_rules_install//:setup.bzl", "install_rules_setup")

install_rules_setup()
