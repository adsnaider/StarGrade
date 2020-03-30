# StarGrade

StarGrade is a language-agnostic framework that allows you to create a
composite Gradescope assignment.

<!-- vim-markdown-toc GFM -->

* [Goals](#goals)
* [Non-Goals](#non-goals)
* [Motivation](#motivation)
  * [Language Agnostic](#language-agnostic)
  * [Composite](#composite)
  * [Easy to Setup](#easy-to-setup)
  * [Robust](#robust)
  * [Fast to Run](#fast-to-run)
  * [Secure](#secure)
* [Design Overview](#design-overview)
* [Installation](#installation)
* [Usage](#usage)
* [Developer Overview](#developer-overview)

<!-- vim-markdown-toc -->


## Goals

- Language agnostic
- Composite
- Easy to setup
- Robust
- Fast to run autograder
- Secure

## Non-Goals

- Not an interface to Gradescope (see
  [Git-Scope](https://github.com/adsnaider/Git-Scope/blob/master/README.md))

## Motivation

Creating an autograded assignment in Gradescope is hard for many reasons. It
requires a lot of code

- Installing dependencies in docker container
- Cloning/Pulling the autograder repo
- Moving and processing submission files around
- Running the test code
- Converting the test results into a [`results.json` as shown in the Gradescope
  Specs](https://gradescope-autograders.readthedocs.io/en/latest/specs/)

A lot of this code can be abstracted away. This is the problem StarGrade aims to
fix.

### Language Agnostic

We want the code to be language agnostic for 2 main reasons.

1. Different courses use different programming languages.

  This one is fairly self explanatory. We want to run test code in many
  different languages C++, Java, Python, etc...

1. Some tests aren't language dependent.

  Some educators may choose to have Gradescope tests that are checking that the
  code compiles or that the correct files were submitted. Another case might be
  if an educator wants to have a diff test. All of these tests can be
  written very easily in bash.

### Composite

Composite in the scope of StarGrade just means that it can have tests written in
different languages. The idea is that StarGrade can be configured to run
different suite of tests. A suite of tests could, for instance, be:

- Preprocessing tests

  These could be tests that just check that the submission is what was expected.

- Correctness tests

  This would be your actual test cases to test that check the students code is
  _corect_.

### Easy to Setup

This one is fairly self explanatory. We want to make our migration steps as
simple and painless as possible. If it's easy to setup then it's also easy to
migrate too. We also want to be able to create new labs easily without having
to go through too many iterations to get it right.

### Robust

Any time StarGrade breaks, the autograders will need to be rebuilt since
Gradescope freezes the server's disk after installation. Therefore, every
release of StarGrade should be well tested to avoid the abovementioned event.

### Fast to Run

There will be many students running/testing their code against Gradescope many
times. We want to give our students feedback as early as possible so that they
can fix any issues they may have. We decided that it is more important for
StarGrade to be fast to run rather than fast to setup.

### Secure

We don't want the submitted code to be able to mess with Gradescope's internal
structure (change the results, read the SSH keys, etc.).

## Design Overview

StarGrade works by separating test modules into their own process. When an
educator is writing the configuration for their assignment, each test suite will
have an *execute command*. StarGrade will create a new process for each test
suite with the command given. The test program will output the results to STDOUT
which StarGrade will be able to read and interpret. StarGrade will run all of
the test suites and collect the test outputs for all of them. Once all the
programs are done running, StarGrade will combine them into a single data
structure and will output the results in a JSON format following [Gradescope's
specification](https://gradescope-autograders.readthedocs.io/en/latest/specs/).

## Installation

Currently, the only way to install StarGrade is by going into the release page
in Github and downloading and installing the `.deb` package. This will only work
for debian-based linux systems.

## Usage

Let's assume you have your unit tests (written with Google Test) that check
whether a particular piece of code is working. The code might look like this

```c++
// test.cc
#include <gtest/gtest.h>

TEST(MyTestSuite, MyTest1) {
  EXPECT_TRUE(something);
  EXPECT_EQ(something, something_equal);
}

TEST(MyTestSuite, MyTest2) {
  FAIL() << "I guess we can't pass this test.";
}

// Note how we don't have a main (this is important).
```

Your Makefile should then look like this

```makefile
# Makefile
test: test.cc
	g++ -std=c++11 -o test test.cc -lgtest -lgtest_main -lpthread
```

StarGrade doesn't require you to modify the test code. Instead, all you have to
do is create a second target in your Makefile. The new target will use the same
file but will use different dependencies. It should look like this

```makefile
# Makefile
test: test.cc
	g++ -std=c++11 -o test test.cc -lgtest -lgtest_main -lpthread

startest: test.cc
	g++ -std=c++11 -o test test.cc -lgtest -lgradescope_test_main
    -lgradescope_test_listener -lpthread
```

So the `./test` target is the same. That means that you can continue to
test the code with that. However, now you have a new target `./startest` that
instead of writing the normal STDOUT, it will write the output of the results in
a structured format that StarGrade can collect and process to generate the
`results.json`.


Last step is to create the configuration file. This configuration will include
some information about each particular test (score, name, visibility, etc.)

```yaml
# config.yaml
stdout_visibility: hidden
output: My First Gradescope Assignment with StarGrade

test_parts:
  - run: ./startest
  tests:
    - id: MyTestSuite-MyTest1
      max_score: 10
      name: Testing something here
      visibility: visible

    - id: MyTestSuite-MyTest2
      max_score: 10
      name: This will just fail
      visibility: after_due_date
```

Most fields in the configuration are the same as the ones in the [gradescope
specification](https://gradescope-autograders.readthedocs.io/en/latest/specs/).
One thing to note is that each element in `test_parts` will have a `run`
field. This is simply the test executable that we created.
The other thing to note is the `id`. For GTest tests, the `id` should match
exactly the pattern `TestSuite`-`TestName`.

Now you can generate the `results.json` by running the following command

```shell
starrun --pwd=$PWD --config=config.yaml --results=results/results.json
```

which will generate the results in `results/results.json`

`starrun` is a binary that was installed with the StarGrade package.

Note that starrun has 3 arguments
- pwd: Usually set to the head of the repo.
- config: YAML configuration file that defines the test suites.
- results: JSON file output where the results are saved.

Note: Currently StarGrade only supports GTest (more test frameworks are coming
soon)

## Developer Overview

[This section is currently under development]
