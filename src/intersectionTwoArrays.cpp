// https://leetcode.com/problems/intersection-of-two-arrays/
//
// Status: Accepted
// Runtime: 4 ms
// Score: 99.38 %
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
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        map<int, int> vals;
        map<int, int> common;

        // Keep track of all unique numbers in the the first vector
        for (auto n : nums1)
        {
            vals[n] = 1;
        }

        // Find matching numbers in the second vector
        for (auto n : nums2)
        {
            if (vals[n])
            {
                common[n] = 1;
            }
        }

        vector<int> intersections;
        for (auto c : common)
        {
            intersections.push_back(c.first);
        }

        return intersections;
    }
};

TEST(Solution, Example1)
{
    Solution solution;
    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {2, 2};
    vector<int> answer = {2};

    ASSERT_EQ(solution.intersection(nums1, nums2), answer);
}

TEST(Solution, Example2)
{
    Solution solution;
    vector<int> nums1 = {4, 9, 5};
    vector<int> nums2 = {9, 4, 9, 8, 4};
    vector<int> answer = {9, 4};

    ASSERT_EQ(solution.intersection(nums1, nums2), answer);
}