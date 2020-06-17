package(default_visibility = ["//visibility:__pkg__"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

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

cc_library(
    name = "gradescope_part_results",
    srcs = ["gradescope_part_results.cc"],
    hdrs = ["gradescope_part_results.h"],
    deps = [
        ":gradescope_test_results",
        "@nlohmann//:json",
        "@yaml_cpp//:yaml-cpp",
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

cc_library(
    name = "gradescope_visibility",
    hdrs = ["gradescope_visibility.h"],
    deps = [
    ],
)

proto_library(
    name = "gradescope_part_proto",
    srcs = ["gradescope_part.proto"],
)

cc_proto_library(
    name = "gradescope_part_cc_proto",
    deps = [":gradescope_part_proto"],
)

cc_grpc_library(
    name = "gradescope_part_cc_grpc",
    srcs = [":gradescope_part_proto"],
    grpc_only = True,
    deps = [":gradescope_part_cc_proto"],
)

cc_library(
    name = "gradescope_part_server",
    srcs = ["gradescope_part_server.cc"],
    deps = [":gradescope_part_cc_grpc"],
)
