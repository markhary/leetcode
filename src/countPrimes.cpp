// https://leetcode.com/problems/count-primes/
//
// Status: Accepted
// Runtime: 16 ms
// Score: 97.57 %
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
    int countPrimes(int n)
    {
        int numPrimes = 0;

        // By definition, 1 is not a prime
        if (n == 1)
            return 0;

        // Making this bigger to not deal with 0-indexing issue
        bool *notPrimes = new bool[n + 1]();

        for (int i = 2; i < n; i++)
        {
            // Don't bother if this isn't a prime
            if (notPrimes[i])
            {
                continue;
            }
            numPrimes++;
            notPrimes[i] = true;

            // Mark off all multiples as not a prime
            for (int j = 1; (j * i) < n; j++)
            {
                notPrimes[j * i] = true;
            }
        }
        return numPrimes;
    };
};

TEST(CountPrimes, Examples)
{
    Solution solution;
    ASSERT_EQ(solution.countPrimes(10), 4);
    ASSERT_EQ(solution.countPrimes(0), 0);
    ASSERT_EQ(solution.countPrimes(1), 0);
}