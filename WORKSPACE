workspace(name = "StarGrade")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
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

http_archive(
    name = "nlohmann",
    build_file = "@//third_party/rules:BUILD.nlohmann",
    sha256 = "87b5884741427220d3a33df1363ae0e8b898099fbc59f1c451113f6732891014",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip"],
)

http_archive(
    name = "rules_pkg",
    sha256 = "4ba8f4ab0ff85f2484287ab06c0d871dcb31cc54d439457d28fd4ae14b18450a",
    url = "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.4/rules_pkg-0.2.4.tar.gz",
)

# PROTOBUFS
# rules_cc defines rules for generating C++ code from Protocol Buffers.
http_archive(
    name = "rules_cc",
    sha256 = "ce19fea12ee666a0d399e6e15b5a77264f6da2b70f2759adea767c9a7f79b17c",
    strip_prefix = "rules_cc-5cbd3dfbd1613f71ef29bbb7b10310b81e272975",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/5cbd3dfbd1613f71ef29bbb7b10310b81e272975.tar.gz",
        "https://github.com/bazelbuild/rules_cc/archive/5cbd3dfbd1613f71ef29bbb7b10310b81e272975.tar.gz",
    ],
)

# rules_proto defines abstract rules for building Protocol Buffers.
http_archive(
    name = "rules_proto",
    sha256 = "dedb72afb9476b2f75da2f661a00d6ad27dfab5d97c0460cf3265894adfaf467",
    strip_prefix = "rules_proto-486aaf1808a15b87f1b6778be6d30a17a87e491a",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/486aaf1808a15b87f1b6778be6d30a17a87e491a.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/486aaf1808a15b87f1b6778be6d30a17a87e491a.tar.gz",
    ],
)

load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")

rules_cc_dependencies()

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

http_archive(
    name = "com_github_grpc_grpc",
    strip_prefix = "grpc-de893acb6aef88484a427e64b96727e4926fdcfd",
    urls = [
        "https://github.com/grpc/grpc/archive/de893acb6aef88484a427e64b96727e4926fdcfd.tar.gz",
    ],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

# Not mentioned in official docs... mentioned here https://github.com/grpc/grpc/issues/20511
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()
