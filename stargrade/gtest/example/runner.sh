#/bin/bash

#echo "$@"
bazel run :example_test -- "$@"
