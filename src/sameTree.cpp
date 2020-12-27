// https://leetcode.com/problems/same-tree/
//
// Status: Accepted
// Runtime: 8ms
// Score: 97.83%
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "leetcode.h"
#include "macros.h"

using namespace std;

class Solution
{
public:
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        bool same = true;

        if (p && q)
        {
            return ((p->val == q->val) &&
                    (isSameTree(p->left, q->left)) &&
                    (isSameTree(p->right, q->right)));
        }
        else if (p || q)
        {
            same = false;
        }

        return same;
    }
};

TEST(SameTree, Sample)
{
    TreeNode p[3] = {1, 2, 3};
    TreeNode q[3] = {1, 2, 3};

    p[0].left = &p[1];
    p[0].right = &p[2];
    q[0].left = &q[1];
    q[0].right = &q[2];

    Solution solution;
    ASSERT_EQ(solution.isSameTree(p, q), true);

    p[0].left = nullptr;
    ASSERT_EQ(solution.isSameTree(p, q), false);
}

TEST(SameTree, Empty)
{
    Solution solution;
    ASSERT_EQ(solution.isSameTree(nullptr, nullptr), true);
}

TEST(SameTree, Simple)
{
    TreeNode p(5);
    Solution solution;

    ASSERT_EQ(solution.isSameTree(&p, nullptr), false);
}
