#ifndef LEETCODE_H
#define LEETCODE_H

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *n) : val(x), next(n) {}
};

#define PRINT_LISTNODE(X)                                            \
  {                                                                  \
    cout << #X << ": " << ((X == nullptr) ? "nullptr" : "") << endl; \
    ListNode *x = X;                                                 \
    while (x != nullptr)                                             \
    {                                                                \
      cout << " " << #X << " -> " << x->val << endl;                 \
      x = x->next;                                                   \
    }                                                                \
  }

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#endif