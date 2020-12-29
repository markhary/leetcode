// https://leetcode.com/problems/linked-list-cycle/
//
// Status: Accepted
// Runtime: 20 ms
// Score: 13.67 %
//

#include <iostream>
#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "leetcode.h"
#include "macros.h"

using namespace std;

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        unordered_map<ListNode *, int> nodes;

        ListNode *node = head;

        while (node)
        {
            if (nodes[node->next])
            {
                return true;
            }

            nodes[node->next] = 1;
            node = node->next;
        }

        return false;
    }
};

TEST(LinkedListCycle, Example1)
{
    Solution solution;
    ListNode node3(3);
    ListNode node2(2);
    ListNode node0(0);
    ListNode node_4(-4);
    node3.next = &node2;
    node2.next = &node0;
    node0.next = &node_4;
    node_4.next = &node2;
    ListNode *head = &node3;

    ASSERT_EQ(solution.hasCycle(head), true);
}

TEST(LinkedListCycle, Example2)
{
    Solution solution;
    ListNode node1(1);
    ListNode node2(2);

    node1.next = &node2;
    node2.next = &node1;
    ListNode *head = &node1;

    ASSERT_EQ(solution.hasCycle(head), true);
}

TEST(LinkedListCycle, Example3)
{
    Solution solution;
    ListNode node1(1);
    ListNode *head = &node1;

    ASSERT_EQ(solution.hasCycle(head), false);
}