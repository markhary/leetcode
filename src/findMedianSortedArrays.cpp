// https://leetcode.com/problems/median-of-two-sorted-arrays/
// 
// Status: Accepted
// Runtime: 4 ms
// Score: 91.99%
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution {
    public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const int M  = nums1.size();
        const int N  = nums2.size();
        vector<int> combined(M+N,0);

        int m = 0;
        int n = 0;
        int c = 0;

		// The solution implemented is O(N+M)
        if ( !M ) {
            combined  = nums2;
        } else if ( !N ) {
            combined  = nums1;
        } else {
            while ((m<M) && (n<N)) {
                while ((m<M) && (nums1[m] <= nums2[n]))  {
                    combined[c] = nums1[m];
					c++;
                    m++;
                }
                while ((n<N) && (nums2[n] <= nums1[m])) {
                    combined[c] = nums2[n];
                    c++;
                    n++;
                }
                while ((m>=M) && (n<N)) {
                    combined[c++] = nums2[n++];
                }
                while ((n>=N) && (m<M)) {
                    combined[c++] = nums1[m++];
                }
            }
        }
        
        int C = combined.size();
        double median = 0.0;
        if ( C == 1 ) {
            median = combined[0];
        } else if ( C%2 ) {
            median = combined[C/2];
        } else {
            int c = C/2;
            median = ((double)combined[c] + (double)combined[c-1]) / 2.0;
        }
        return median;
    }
};

TEST(FindMedianSortedArrays, Sample)
{
    Solution solution;
    vector<int> a = {1, 2};
    vector<int> b = {3, 4};

    ASSERT_EQ(solution.findMedianSortedArrays(a, b), 2.5);

    a = {1, 3};
    b = {2};
    ASSERT_EQ(solution.findMedianSortedArrays(a, b), 2.0);
}

TEST(FindMedianSortedArrays, RunTime)
{
    Solution solution;
    vector<int> a = {};
    vector<int> b = {1};

    ASSERT_EQ(solution.findMedianSortedArrays(a, b), 1.0);

    a = {100001};
    b = {100000};
    ASSERT_EQ(solution.findMedianSortedArrays(a, b), 100000.5);
}
