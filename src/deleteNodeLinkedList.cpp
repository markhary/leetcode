// https://leetcode.com/problems/delete-node-in-a-linked-list/
//
// Status: Accepted
// Runtime: 8 ms
// Score: 99.75 %
//

#include <gtest/gtest.h>
#include "args.h"
#include "leetcode.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution
{
public:
    void deleteNode(ListNode *node)
    {
        // 4 -> 5 -> 1 -> 9 -> null;
        // Shift all nodes to the left
        // delete the last one

        ListNode *prev = node;
        while (node->next != NULL)
        {
            node->val = node->next->val;
            prev = node;
            node = node->next;
        }
        prev->next = NULL;

        // Method is called delete node, but
        // I do not know who owns it so I won't touch it
        // delete node;
    }
};

namespace test
{
    static void create(vector<int> values, vector<ListNode> &nodes)
    {
        for (auto &v : values)
        {
            nodes.push_back(ListNode(v));
        }

        int N = nodes.size();
        for (int n = 1; n < N; n++)
        {
            nodes[n - 1].next = &nodes[n];
        }
    }

    static vector<int> unpack(vector<ListNode> &nodes)
    {
        vector<int> output;

        if (nodes.size() == 0)
        {
            return output;
        }

        ListNode *node = &nodes[0];
        while (node)
        {
            output.push_back(node->val);
            node = node->next;
        }

        return output;
    }
} // namespace test

TEST(DeleteNodeLinkedList, Example1)
{
    Solution solution;
    vector<int> input = {4, 5, 1, 9};
    vector<int> output = {4, 1, 9};

    vector<ListNode> nodes;
    test::create(input, nodes);
    solution.deleteNode(&nodes[1]);
    vector<int> answer = test::unpack(nodes);

    ASSERT_EQ(answer, output);
}

TEST(DeleteNodeLinkedList, Example2)
{
    Solution solution;
    vector<int> input = {4, 5, 1, 9};
    vector<int> output = {4, 5, 9};

    vector<ListNode> nodes;
    test::create(input, nodes);
    solution.deleteNode(&nodes[2]);
    vector<int> answer = test::unpack(nodes);

    ASSERT_EQ(answer, output);
}

TEST(DeleteNodeLinkedList, Example3)
{
    Solution solution;
    vector<int> input = {1, 2, 3, 4};
    vector<int> output = {1, 2, 4};

    vector<ListNode> nodes;
    test::create(input, nodes);
    solution.deleteNode(&nodes[2]);
    vector<int> answer = test::unpack(nodes);

    ASSERT_EQ(answer, output);
}

TEST(DeleteNodeLinkedList, Example4)
{
    Solution solution;
    vector<int> input = {0, 1};
    vector<int> output = {1};

    vector<ListNode> nodes;
    test::create(input, nodes);
    solution.deleteNode(&nodes[0]);
    vector<int> answer = test::unpack(nodes);

    ASSERT_EQ(answer, output);
}

TEST(DeleteNodeLinkedList, Example5)
{
    Solution solution;
    vector<int> input = {-3, 5, -99};
    vector<int> output = {5, -99};

    vector<ListNode> nodes;
    test::create(input, nodes);
    solution.deleteNode(&nodes[0]);
    vector<int> answer = test::unpack(nodes);

    ASSERT_EQ(answer, output);
}