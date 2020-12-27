// https://leetcode.com/problems/validate-binary-search-tree/
//
// Status: Accepted
// Runtime: 12 ms
// Score: 90.53 %
//

#include <iostream>
#include <queue>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "leetcode.h"
#include "macros.h"

using namespace std;

class Solution
{
public:
    bool isValidBST(TreeNode *root)
    {
        bool isValid = true;
        std::queue<int> elements;

        isValid = isValidBST(root, &elements);
        if (elements.size() < 2)
        {
            return isValid;
        }

        // Go through all of the elements, they should be in order
        int prev = elements.front();
        elements.pop();

        while (isValid && !elements.empty())
        {
            auto e = elements.front();
            if (e <= prev)
            {
                isValid = false;
                break;
            }
            elements.pop();
            prev = e;
        }

        return isValid;
    }

    bool isValidBST(TreeNode *root, std::queue<int> *elements)
    {
        if (!root)
            return true;
        bool valid = true;

        if (root->left)
        {
            valid &= isValidBST(root->left, elements);
            valid &= (root->left->val < root->val);
        }
        elements->push(root->val);
        if (root->right)
        {
            valid &= isValidBST(root->right, elements);
            valid &= (root->right->val > root->val);
        }

        return valid;
    }
};

TEST(ValidateBinarySourceTree, Example1)
{
    Solution solution;

    TreeNode node1(1);
    TreeNode node3(3);
    TreeNode node2(2, &node1, &node3);

    TreeNode *root = &node2;

    ASSERT_EQ(solution.isValidBST(root), true);
}

TEST(ValidateBinarySourceTree, Example2)
{
    Solution solution;

    TreeNode node3(3);
    TreeNode node6(6);
    TreeNode node4(4, &node3, &node6);
    TreeNode node1(1);
    TreeNode node5(5, &node1, &node4);

    TreeNode *root = &node5;

    ASSERT_EQ(solution.isValidBST(root), false);
}