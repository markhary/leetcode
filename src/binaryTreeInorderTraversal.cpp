// https://leetcode.com/problems/binary-tree-inorder-traversal/
// 
// Status: Accepted
// Runtime: 0 ms
// Score: 100 %
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
    public:
    vector<int> inorderTraversal(TreeNode* root) {
        // inorder traversal is Left-Root-Right
        vector<int> answer;

        // Don't do anything if root is null
        if ( root != nullptr ) {
            // Handle the left root
            if ( root->left != nullptr ) {
                vector<int> temp = inorderTraversal(root->left);
                answer.insert(answer.end(), temp.begin(), temp.end());
            }
            // handle the Root
            if (root != nullptr) {
                answer.push_back(root->val);
            } 
            
            // handle Right
            if (root->right != nullptr){
                vector<int> temp = inorderTraversal(root->right);
                answer.insert(answer.end(), temp.begin(), temp.end());
            } 
        } 

        return answer;
    }
};

TEST(BinaryTreeInorderTraversal, CorrectSample)
{
    Solution solution;
    vector<int> correct = {1, 3, 2};

    TreeNode node1(1);
    TreeNode node2(2);
    TreeNode node3(3);

    TreeNode *root = &node1;
    node1.right = &node2;
    node2.left = &node3;

    ASSERT_EQ(solution.inorderTraversal(root), correct);
}

TEST(BinaryTreeInorderTraversal, Empty)
{
    Solution solution;
    vector<int> empty;

    ASSERT_EQ(solution.inorderTraversal(nullptr), empty);
}
