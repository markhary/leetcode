// https://leetcode.com/problems/two-sum/
// 
// Status: Accepted
// Runtime: 8ms
// Score: 97.83%
//

#include <iostream>
#include <map>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) 
        {
            std::map<int, int> map;
            std::map<int, int>::iterator it;
            for (int i=0; i<(int)nums.size(); i++) {
                int remainder = target - nums[i];
                it = map.find(remainder);
                if (it != map.end() ) {
                    return vector<int>{ map[remainder], i};
                }   
                map[nums[i]] = i;
            }
            throw "No solution found";
        }
};


TEST(TwoSumsTest, CorrectSample)
{
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> correct = {0, 1};
    Solution solution;

    try {
        ASSERT_EQ(solution.twoSum(nums, target), correct);
    } catch (...) {
        std::cout << "TwoSumsTest.CorrectSample: Exception thrown" << endl;
    }
}


TEST(TwoSumsTest, NoSolution)
{
    vector<int> nums = {2, 7, 11, 15};
    int target = 95;
    bool exceptionThrown = false;
    vector<int> ignoreAnswer;

    try {
        Solution solution;
        ignoreAnswer = solution.twoSum(nums, target);
    } catch (...) {
        exceptionThrown = true;
    }

    ASSERT_EQ(exceptionThrown, true);
}
