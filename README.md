# LeetCode Solutions

## Lessons

Here are my solutions to the LeetCode lessons. You can find the lessons [here](https://leetcode.com/problemset/all/).

Details Legend: D = _Difficulty_; S = _Score_; RT = _Runtime_

| \#  | Task - Solution                                                                                                                                                              | Details                                                                                                                                                                      |
| --- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1   | [TwoSum](https://leetcode.com/problems/two-sum/).[cpp](src/twoSum.cpp)                                                                                                       | ![](https://img.shields.io/badge/D-easy-green.svg) ![](https://img.shields.io/badge/S-97.83%25-green.svg) ![](https://img.shields.io/badge/RT-8%20ms-lightgrey.svg)          |
| 2   | [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/).[cpp](src/addTwoNumbers.cpp)                                                                               | ![](https://img.shields.io/badge/D-medium-yellow.svg) ![](https://img.shields.io/badge/S-99.00%25-green.svg) ![](https://img.shields.io/badge/RT-28%20ms-lightgrey.svg)      |
| 3   | [Longest Substring](https://leetcode.com/problems/longest-substring-without-repeating-characters/).[cpp](src/longestSubstring.cpp)                                           | ![](https://img.shields.io/badge/D-medium-yellow.svg) ![](https://img.shields.io/badge/S-93.12%25-green.svg) ![](https://img.shields.io/badge/RT-24%20ms-lightgrey.svg)      |
| 4   | [Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/).[cpp](src/findMedianSortedArrays.cpp)                                              | ![](https://img.shields.io/badge/D-hard-red.svg) ![](https://img.shields.io/badge/S-91.99%25-green.svg) ![](https://img.shields.io/badge/RT-40%20ms-lightgrey.svg)           |
| 5   | [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/).[cpp](src/longestPalindromicSubstring.cpp)                                     | ![](https://img.shields.io/badge/D-medium-yellow.svg) ![](https://img.shields.io/badge/S-0.0%25-red) ![](https://img.shields.io/badge/RT-%2D-%20ms-lightgrey.svg)            |
| 36  | [Valid Sudoku](https://leetcode.com/problems/valid-sudoku/).[cpp](src/validSudoku.cpp)                                                                                       | ![](https://img.shields.io/badge/D-medium-yellow.svg) ![](https://img.shields.io/badge/S-81.5%25-yellow) ![](https://img.shields.io/badge/RT-32%20ms-lightgrey.svg)          |
| 94  | [Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/).[cpp](src/binaryTreeInorderTraversal.cpp)                                      | ![](https://img.shields.io/badge/D-medium-yellow.svg) ![](https://img.shields.io/badge/S-100%25-green.svg) ![](https://img.shields.io/badge/RT-0%20ms-lightgrey.svg)         |
| 100 | [Same Tree](https://leetcode.com/problems/same-tree/).[cpp](src/sameTree.cpp)                                                                                                | ![](https://img.shields.io/badge/D-easy-green.svg) ![](https://img.shields.io/badge/S-76.32%25-yellow.svg) ![](https://img.shields.io/badge/RT-4%20ms-lightgrey.svg)         |
| 175 | [Combine Two Tables](https://leetcode.com/problems/combine-two-tables/).[sql](sql/combineTwoTables.sql)                                                                      | ![](https://img.shields.io/badge/D-easy-green.svg) ![](https://img.shields.io/badge/S-87.47%25-lightgrey.svg) ![](https://img.shields.io/badge/RT-208%20ms-lightgrey.svg)    |
| 176 | [Second Hightest Salary](https://leetcode.com/problems/second-highest-salary/).[sql](sql/secondHighestSalary.sql)                                                            | ![](https://img.shields.io/badge/D-easy-green.svg) ![](https://img.shields.io/badge/S-84.77%25-lightgrey.svg) ![](https://img.shields.io/badge/RT-127%20ms-lightgrey.svg)    |
| 177 | [Nth Hightest Salary](https://leetcode.com/problems/nth-highest-salary/).[sql](sql/nthHighestSalary.sql)                                                                     | ![](https://img.shields.io/badge/D-medium-yellow.svg) ![](https://img.shields.io/badge/S-14.10%25-lightgrey.svg) ![](https://img.shields.io/badge/RT-212%20ms-lightgrey.svg) |
| 178 | [Rank Scores](https://leetcode.com/problems/rank-scores/).[sql](sql/rankScores.sql)                                                                                          | ![](https://img.shields.io/badge/D-medium-yellow.svg) ![](https://img.shields.io/badge/S-88.10%25-lightgrey.svg) ![](https://img.shields.io/badge/RT-183%20ms-lightgrey.svg) |
| 181 | [Employees Earning More Than Their Managers](https://leetcode.com/problems/employees-earning-more-than-their-managers/).[sql](sql/employeesEarningMoreThanTheirManagers.sql) | ![](https://img.shields.io/badge/D-easy-green.svg) ![](https://img.shields.io/badge/S-72.76%25-lightgrey.svg) ![](https://img.shields.io/badge/RT-298%20ms-lightgrey.svg)    |

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

Assuming you are using cmake, tests will be located in your `$BUILD_DIR}/bin` directory. All tests are in the same `leetcode` binary. Individual tests can be run per the [googletest framework documentation](https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#running-test-programs-advanced-options). Here is a quick reference:

```
/path/to/build/bin> leetcode --help
/path/to/build/bin> leetcode --gtest_list_tests
/path/to/build/bin> leetcode --gtest_filter=TestName.Test
/path/to/build/bin> leetcode --seed 12345
```

### Dependencies

Test are built using the following packages. Use CMake and the dependencies will be downloaded and built for you.

- [gflags](https://gflags.github.io/gflags/)
- [googletest](https://github.com/google/googletest)

### Building

Use cmake and conan:

1. `mkdir build && cd build`
2. `conan install ..`
3. `cmake ..`
4. `make`

NOTICE: On Ubuntu, you will need to do an extra step: `conan profile update settings.compiler.libcxx=libstdc++11 default`. See step #5 [for details](https://docs.conan.io/en/latest/getting_started.html).

Executables will be located in your `$BUILD_DIR}/bin` directory. Libraries will be located in your `$BUILD_DIR}/lib` directory.

You can build the tests for your favorite development environment using `cmake`. e.g.:

- For the command line:

```shell
mkdir test/build
cd test/build
conan install ..
cmake ..
make
```

- For XCode:

```shell
mkdir test/xcode
cd test/xcode
conan install ..
cmake -G Xcode ..
make
```

Tests will be created in the `bin` directory located wherever you ran cmake from (`test\build\bin` in the example above).

## Contributing

You are welcome to contribute provided you accept the [Contributor Covenant Code of Conduct](CONTRIBUTING.md).

## License

This repository is licensed under [The Unlicense](LICENSE.md).

## Acknowledgements

- Thank you to the [gflags](https://gflags.github.io/gflags/) command line parsing library.
- Thank you to the [googletest](https://github.com/google/googletest) C++ test framework.
