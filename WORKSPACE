workspace(name = "StarGrade")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "yaml_cpp",
    commit = "de8253fcb075c049c4ad1c466c504bf3cf022f45",
    remote = "git@github.com:jbeder/yaml-cpp.git",
)

http_archive(
    name = "nlohmann",
    build_file = "@//third_party/rules:BUILD.nlohmann",
    urls = ["https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip"],
    sha256 = "87b5884741427220d3a33df1363ae0e8b898099fbc59f1c451113f6732891014",
)
