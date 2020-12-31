// https://leetcode.com/problems/linked-list-cycle/
//
// Status: Accepted
// Runtime: 20 ms
// Score: 98.78 %
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
    bool hash(ListNode *head)
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

    bool fast(ListNode *head)
    {
        ListNode *slow = head;
        if (slow == NULL)
        {
            return false;
        }

        ListNode *fast = head->next;
        if (fast == NULL)
        {
            return false;
        }

        // one goes fast, one goes slow. If we reach a NULL, there is no cycle,
        // otherwise if they overlap, then there is a cycle. Think of this like
        // two runners going around a track - eventually the faster runner will
        // loop past the other one, but they'll be at the same spot

        while (slow != fast)
        {
            if (!fast->next || !fast->next->next)
            {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }

        return true;
    }

    bool hasCycle(ListNode *head)
    {
        //return hash(head);
        return fast(head);
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