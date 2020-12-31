// https://leetcode.com/problems/linked-list-cycle-ii/
//
// Status: Accepted
// Runtime: 20 ms
// Score: 17.31 %
//

#include <array>
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
    ListNode *hash(ListNode *head)
    {
        std::unordered_map<ListNode *, int> nodes;

        ListNode *node = head;

        while (node)
        {
            if (nodes[node])
            {
                return node;
            }
            nodes[node]++;
            node = node->next;
        }
        return nullptr;
    }

    ListNode *race(ListNode *head)
    {
        ListNode *slow = head;
        if (slow == nullptr)
        {
            return nullptr;
        }

        ListNode *fast = head->next;
        if (fast == NULL)
        {
            return nullptr;
        }

        // one goes fast, one goes slow. If we reach a nullptr, there is no cycle,
        // otherwise if they overlap, then there is a cycle. Think of this like
        // two runners going around a track - eventually the faster runner will
        // loop past the other one, but they'll be at the same spot
        int original = 0;
        while (slow != fast)
        {
            original++;
            if (!fast->next || !fast->next->next)
            {
                return nullptr;
            }
            slow = slow->next;
            fast = fast->next->next;
        }

        // We have a cycle, now figure out how long the cycle is
        // by counting the nodes until we lap
        int cycleLength = 0;
        while (!cycleLength || (slow != fast))
        {
            cycleLength++;
            slow = slow->next;
            fast = fast->next->next;
        }

        int offset = original - cycleLength;
        PRINT_VAR(original);
        PRINT_VAR(cycleLength);
        PRINT_VAR(offset);

        if (offset < 0)
        {
            return nullptr;
        }

        ListNode *node = head;
        while (offset--)
        {
            node = node->next;
        }

        return node;
    }

    ListNode *detectCycle(ListNode *head)
    {
        //return race(head);
        return hash(head);
    }
};

TEST(LinkedListCycleII, Example1)
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

    ASSERT_EQ(solution.detectCycle(head), &node2);
}

TEST(LinkedListCycleII, Example2)
{
    Solution solution;
    ListNode node1(1);
    ListNode node2(2);

    node1.next = &node2;
    node2.next = &node1;
    ListNode *head = &node1;

    ASSERT_EQ(solution.detectCycle(head), &node1);
}

TEST(LinkedListCycleII, Example3)
{
    Solution solution;
    ListNode node1(1);
    ListNode *head = &node1;

    ASSERT_EQ(solution.detectCycle(head), nullptr);
}

TEST(LinkedListCycleII, Cycle5)
{
    Solution solution;
    ListNode node0(0);
    ListNode node1(1);
    ListNode node2(2);
    ListNode node3(3);
    ListNode node4(4);

    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node1;

    ListNode *head = &node0;

    ASSERT_EQ(solution.detectCycle(head), &node1);
}

TEST(LinkedListCycleII, Cycle10)
{
    Solution solution;
    const int N = 10;
    array<ListNode, 10> nodes;
    ListNode *head = &nodes[0];

    for (int n = 0; n < (N - 1); n++)
    {
        nodes[n].val = n;
        nodes[n].next = &nodes[n + 1];
    }
    nodes[N - 1].val = N - 1;
    nodes[N - 1].next = &nodes[2];

    ASSERT_EQ(solution.detectCycle(head), &nodes[2]);
}