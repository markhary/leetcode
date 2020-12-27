// https://leetcode.com/problems/remove-nth-node-from-end-of-list
//
// Status: Accepted
// Runtime: 0 ms
// Score: 100%
//

#include <array>
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
    ListNode *to_list(vector<int> input, vector<ListNode> &nodes)
    {
        ListNode *head = NULL;
        if (input.size())
        {
            head = &nodes[0];

            int i = 0;
            ListNode *prev = NULL;

            for (auto &v : input)
            {
                nodes[i].val = v;
                nodes[i].next = NULL;

                if (prev)
                {
                    prev->next = &nodes[i];
                }
                prev = &nodes[i];
                i++;
            }
        }

        return head;
    }

    vector<int> from_list(ListNode *head)
    {
        vector<int> output;

        ListNode *node = head;
        while (node)
        {
            output.push_back(node->val);
            node = node->next;
        }

        return output;
    }

    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        std::array<ListNode *, 30> nodes;
        ListNode *node = head;

        int sz = 0;
        while (node)
        {
            nodes[sz++] = node;
            node = node->next;
        }

        int del = sz - n;

        if (del == 0)
        {
            head = head->next;
        }
        else
        {
            ListNode *prev = nodes[del - 1];
            prev->next = nodes[del]->next;
        }

        return head;
    }
};

TEST(RemoveNthFromEnd, Example)
{
    Solution solution;
    vector<int> input{1, 2, 3, 4, 5};
    vector<int> output{1, 2, 3, 5};
    int n = 2;

    vector<ListNode> inputNodes(input.size()), outputNodes;

    ListNode *input_list = solution.to_list(input, inputNodes);
    ListNode *output_nodes = solution.removeNthFromEnd(input_list, n);
    vector<int> answer = solution.from_list(output_nodes);
    ASSERT_EQ(answer, output);
}