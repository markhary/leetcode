// https://leetcode.com/problems/maximum-depth-of-binary-tree/
//
// Status: Accepted
// Runtime: 8 ms
// Score: 89.25 %
//

#include <array>
#include <iostream>

#include <gtest/gtest.h>
#include "args.h"
#include "leetcode.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        int depth = 1;
        int left = 0;
        int right = 0;

        if (root == NULL)
            return 0;

        if (root->left)
            left = maxDepth(root->left);
        if (root->right)
            right = maxDepth(root->right);

        depth += max(left, right);

        return depth;
    }
};

TEST(MaximumDepthBinaryTree, Example1)
{
    Solution solution;
    TreeNode node15(15), node7(7);
    TreeNode node20(20, &node15, &node7);
    TreeNode node9(9);
    TreeNode node3(3, &node9, &node20);

    TreeNode *root = &node3;

    ASSERT_EQ(solution.maxDepth(root), 3);
}

TEST(MaximumDepthBinaryTree, Example2)
{
    Solution solution;
    TreeNode node2(2);
    TreeNode node1(1, nullptr, &node2);
    TreeNode *root = &node1;

    ASSERT_EQ(solution.maxDepth(root), 2);
}

TEST(MaximumDepthBinaryTree, Example3)
{
    Solution solution;

    ASSERT_EQ(solution.maxDepth(nullptr), 0);
}

TEST(MaximumDepthBinaryTree, Example4)
{
    Solution solution;
    TreeNode node0(0);
    TreeNode *root = &node0;

    ASSERT_EQ(solution.maxDepth(root), 1);
}