// https://leetcode.com/problems/asteroid-collision/
//
// Status: Accepted
// Runtime: 24 ms
// Score: 71.64 %
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

class Solution
{
public:
    vector<int> asteroidCollision(vector<int> &asteroids)
    {
        // Abs.value = size;
        // if a>b, b is removed
        // if a==b, both are removed
        // if b>a, a is removed
        //
        // If positive, moving to right
        // If negative, moving to left

        // Maybe check if asteroid is 0, not sure what
        // to do in that case, behavior is undefined

        std::vector<int> states;

        for (auto a : asteroids)
        {

            bool done = false;

            while (!done)
            {
                // check previous entry to see if these two
                // will collide
                if (states.empty())
                {
                    states.push_back(a);
                    break;
                }

                auto b = states.back();
                // if moving in same direction then no collision
                if (!((a < 0) && (b > 0)))
                {
                    states.push_back(a);
                    break;
                }

                // they are going to collide, see who survives
                if (abs(a) >= abs(b))
                {
                    // Nuke b, keep a. I can actually add this
                    // back to asteroids list
                    states.pop_back();
                }
                if (abs(a) <= abs(b))
                {
                    done = true;
                }
            }
        }

        return states;
    }
};

TEST(AsteroidCollision, Example)
{
    Solution solution;
    vector<int> asteroids{5, 10, -5};
    vector<int> expected{5, 10};

    ASSERT_EQ(solution.asteroidCollision(asteroids), expected);
}