// https://leetcode.com/problems/remove-nth-node-from-end-of-list
//
// Status: Accepted
// Runtime: 0 ms
// Score: 100%
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
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

        delete node;
        return head;
    }
};

TEST(Solution, CorrectTest)
{
    Solution solution;
    bool correct = true;

    try
    {
        ASSERT_EQ(solution.solution(false), correct);
    }
    catch (const exception &e)
    {
        std::cout << "Solution.CorrectTest: Exception - " << e.what() << endl;
    }
}

TEST(Solution, NoSolution)
{
    bool exceptionThrown = false;
    bool ignoreAnswer = true;

    try
    {
        Solution solution;
        ignoreAnswer = solution.solution(true);
    }
    catch (const exception &e)
    {
        exceptionThrown = true;
    }

    ASSERT_EQ(exceptionThrown, true);
}
