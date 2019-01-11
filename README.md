# LeetCode Solutions

## Lessons

Here are my solutions to the LeetCode lessons.  You can find the lessons [here](https://leetcode.com/problemset/all/).

Details Legend: D = *Difficulty*; S = *Score*; RT = *Runtime*

Task - Solution | Details
--------------- | -------
[TwoSum](https://leetcode.com/problems/two-sum/).[cpp](src/twoSum.cpp) | ![](https://img.shields.io/badge/D-easy-green.svg) ![](https://img.shields.io/badge/S-97.83%25-green.svg) ![](https://img.shields.io/badge/RT-8%20ms-lightgrey.svg) 

<!--
| *Lesson Template* | |
// 90-100% Green
// 80-89% - Blue
// 70-79% - Yellow
// 60-69% - Orange
// <60% - Red
[]().[cpp]() | ![](https://img.shields.io/badge/D-easy-green.svg)
[]().[cpp]() | ![](https://img.shields.io/badge/D-medium-yellow.svg)
[]().[cpp]() | ![](https://img.shields.io/badge/D-hard-red.svg)
-->

## Tests
Assuming you are using cmake, tests will be located in your `$BUILD_DIR}/bin` directory.  All tests are in the same `leetcode` binary.  Individual tests can be run per the [googletest framework documentation](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#running-test-programs-advanced-options).  Here is a quick reference:

```
/path/to/build/bin> leetcode --help
/path/to/build/bin> leetcode --gtest_list_tests
/path/to/build/bin> leetcode --gtest_filter=TestName.Test
/path/to/build/bin> leetcode --seed 12345
```

### Dependencies

Test are built using the following packages.  Use CMake and the dependencies will be downloaded and built for you.

* [gflags](https://gflags.github.io/gflags/) 
* [googletest](https://github.com/google/googletest) 


### Building
You can build the tests for your favorite development environment using `cmake`.  e.g.:

* For the command line:

```shell
mkdir test/build
cd test/build
cmake ..
make
```

* For XCode:

```shell
mkdir test/xcode
cd test/xcode
cmake -G Xcode ..
make
```


Tests will be created in the `bin` directory located wherever you ran cmake from (`test\build\bin` in the example above).

## Contributing
You are welcome to contribute provided you accept the [Contributor Covenant Code of Conduct](CONTRIBUTING.md).

## License
This repository is licensed under [The Unlicense](LICENSE.md).

## Acknowledgements
* Thank you to the [gflags](https://gflags.github.io/gflags/) command line parsing library.
* Thank you to the [googletest](https://github.com/google/googletest) C++ test framework.
