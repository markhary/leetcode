// https://leetcode.com/problems/fizz-buzz/
//
// Status: Accepted
// Runtime: 4 ms
// Score: 90.86 %
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution
{
public:
    vector<string> fizzBuzz(int n)
    {

        std::vector<string> output(n, "");
        for (int i = 1; i <= n; i++)
        {
            if (!(i % 15))
                output[i - 1] = "FizzBuzz";
            else if (!(i % 3))
                output[i - 1] = "Fizz";
            else if (!(i % 5))
                output[i - 1] = "Buzz";
            else
                output[i - 1] = to_string(i);
        }
        return output;
    }
};

TEST(FizzBuzz, Example)
{
    Solution solution;
    int n = 15;

    vector<string> answer = {
        "1",
        "2",
        "Fizz",
        "4",
        "Buzz",
        "Fizz",
        "7",
        "8",
        "Fizz",
        "Buzz",
        "11",
        "Fizz",
        "13",
        "14",
        "FizzBuzz"};

    ASSERT_EQ(solution.fizzBuzz(n), answer);
}