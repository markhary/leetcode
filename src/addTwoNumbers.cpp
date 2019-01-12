// https://leetcode.com/problems/two-sum/
// 
// Status: Accepted
// Runtime: 28 ms
// Score: 99.00%
//

#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <cmath>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

#define PRINT_LISTNODE(X) { \
    cout << #X << ": " << ((X == nullptr) ? "nullptr" : "") << endl; \
    ListNode *x = X; \
    while (x != nullptr) {\
        cout << " " << #X << " -> " << x->val << endl; \
        x = x->next; \
    } \
}

// Defined in problem
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
        {
            // Handle case when one of the numbers is null
            if (!l1 && !l2) {
                cout << "somebody was null" << endl;
                return nullptr;
            }

            ListNode *answer = nullptr;
            ListNode *ln = nullptr;

            int carryover = 0;

            // go through and add numbers, linked lists may not be the same length
            do {
                int sum = carryover;
                if ( l1 ) { 
                    sum += l1->val;
                }
                if ( l2 ) {
                    sum += l2->val;   
                }

                int remainder = sum % 10;
                carryover = sum / 10;

                ListNode *node = new ListNode(remainder);
                if (answer == nullptr) {
                    answer = node;
                    ln = node;
                } else {
                    ln->next = node;
                    ln = node;
                }
                if ( l1 ) {
                    l1 = l1->next;
                }
                if (l2 ) {
                    l2 = l2->next;
                }
            } while (l1 || l2);

            // Finally, it is possible the answer may be longer than either of the original
            // linked lists, as indicated by carryover, so add that if carryover is not 0
            if ( carryover ) {
                ListNode *node = new ListNode(carryover);
                ln->next = node;
            }

            return answer;
        }
};

namespace addTwoNumbers {
    namespace test {
        // Create a new list node, don't forget to free
        ListNode *create(int number)
        {
            ListNode *first = nullptr;
            ListNode *prev = nullptr;

            do
            {
                ListNode *ln = new ListNode(number%10);
                number /= 10;

                if (first == nullptr) {
                    first = ln;
                }
                if ( prev != nullptr ) {
                    prev->next = ln;
                }
                prev = ln;

            } while (number);

            return first;
        }

        // Turn the ListNode back into an int
        int unpack(ListNode *listNode)
        {
            if ( listNode == nullptr ) {
                throw "unpack: nullptr passed in";
            }

            int number = 0;
            int i = 0;
            ListNode *ln = listNode;
            while ( ln != nullptr ) {
                number += (ln->val * pow(10, i));
                ln = ln->next;
                i++;
            }

            return number;
        }

        // Free the allocated memory
        void free(ListNode *ln)
        {
            if ( ln == nullptr ) {
                throw "unpack: nullptr passed in";
            }

            while (ln != nullptr) {
                ListNode* next = ln->next;
                delete ln;
                ln = next;
            }
        }
    };
};

TEST(AddTwoNumbersTest, CorrectSample)
{
    const int firstNumber = 342;
    const int secondNumber = 465;

    ListNode *first = addTwoNumbers::test::create(firstNumber);
    ListNode *second = addTwoNumbers::test::create(secondNumber);
    Solution solution;

    int answerInteger = 0;
    int lookingFor = firstNumber + secondNumber;

    try {
        ListNode *answer = solution.addTwoNumbers(first, second);
        answerInteger = addTwoNumbers::test::unpack(answer);
        addTwoNumbers::test::free(answer);
        addTwoNumbers::test::free(first);
        addTwoNumbers::test::free(second);
    } catch (...) {
        cout << "TwoSumsTest.CorrectSample:: Caught exception" << endl;
    }

    ASSERT_EQ(answerInteger, lookingFor);
}
