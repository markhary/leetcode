// https://leetcode.com/problems/linked-list-cycle-ii/
//
// Status: Accepted
// Runtime: 8 ms
// Score: 71.74 %
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
        ListNode *fast = slow;

        if (head == nullptr)
        {
            return nullptr;
        }

        // one goes fast, one goes slow. If we reach a nullptr, there is no cycle,
        // otherwise if they overlap, then there is a cycle. Think of this like
        // two runners going around a track - eventually the faster runner will
        // loop past the other one, but they'll be at the same spot
        int distance = 0;
        while (!distance || (slow != fast))
        {
            distance++;
            if (!fast->next || !fast->next->next)
            {
                return nullptr;
            }
            slow = slow->next;
            fast = fast->next->next;
        }

        // Advance each node until they intersect again
        ListNode *intersection = fast;
        slow = head;

        while (slow != intersection)
        {
            slow = slow->next;
            intersection = intersection->next;
        }

        return slow;
    }

    ListNode *detectCycle(ListNode *head)
    {
        return race(head);
        //return hash(head);
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

TEST(LinkedListCycleII, Sweep)
{
    Solution solution;

    const int N = 20;

    int tests = 0;
    int passed = 0;
    for (int n = 1; n < N; n++)
    {
        array<ListNode, N> nodes;
        ListNode *head = &nodes[0];

        for (int m = 0; m < n; m++)
        {
            nodes[m].val = m;
            nodes[m].next = &nodes[m + 1];
        }

        for (int m = 0; m < n; m++)
        {
            tests++;
            nodes[n - 1].next = &nodes[m];

            ListNode *node = solution.detectCycle(head);
            EXPECT_EQ(node, &nodes[m]);

            bool result = (node == &nodes[m]);
            if (result)
            {
                passed++;
            }
        }
    }
    ASSERT_EQ(tests, passed);
}