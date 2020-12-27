// URL to leetcode exercise
// 
// Status: (Not) Accepted
// Runtime: 8 ms
// Score: X.Y %
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution {
    public:
        bool solution(bool throwError) 
        {
            if ( throwError ) {
                throw "No solution found";
            }
            return throwError;
        }
};


TEST(Solution, CorrectTest)
{
    Solution solution;
    bool correct = true;

    try {
        ASSERT_EQ(solution.solution(false), correct);
    } catch (const exception &e) {
        std::cout << "Solution.CorrectTest: Exception - " << e.what() << endl;
    }
}


TEST(Solution, NoSolution)
{
    bool exceptionThrown = false;
    bool ignoreAnswer = true;

    try {
        Solution solution;
        ignoreAnswer = solution.solution(true);
    } catch (const exception &e) {
        exceptionThrown = true;
    }

    ASSERT_EQ(exceptionThrown, true);
}
