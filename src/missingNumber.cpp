// https://leetcode.com/problems/missing-number/
//
// Status: Accepted
// Runtime: 20 ms
// Score: 98.21 %
//

#include <iostream>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution
{
public:
    int missingNumber(vector<int> &nums)
    {
        int n = nums.size();
        return (n) * (n + 1) / 2 - std::accumulate(nums.begin(), nums.end(), 0);
    }
};

TEST(MissingNumber, Example1)
{
    Solution solution;
    vector<int> numbers = {3, 0, 1};
    int answer = 2;

    ASSERT_EQ(solution.missingNumber(numbers), answer);
}

TEST(MissingNumber, Example2)
{
    Solution solution;
    vector<int> numbers = {0, 1};
    int answer = 2;

    ASSERT_EQ(solution.missingNumber(numbers), answer);
}

TEST(MissingNumber, Example3)
{
    Solution solution;
    vector<int> numbers = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    int answer = 8;

    ASSERT_EQ(solution.missingNumber(numbers), answer);
}

TEST(MissingNumber, Example4)
{
    Solution solution;
    vector<int> numbers = {0};
    int answer = 1;

    ASSERT_EQ(solution.missingNumber(numbers), answer);
}