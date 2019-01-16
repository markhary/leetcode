// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// 
// Status: Accepted
// Runtime: 24 ms
// Score: 93.12 %
//

#include <iostream>
#include <map>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

class Solution {
public:
    
    int lengthOfLongestSubstring(string s) {
        // Can be any character, not just alphabet
        // Allow for all ASCII characters
        vector<bool> characters(128, false);
        
        int N = s.length();
        int i=0;
        int j=0;
        
        int maxCount = 0;
        
        // Use caterpillar method to inch along finding long substrings
        // Use a 32-bit int for tracking characters
        // Use counter just so I don't have to count elements
        while ( (i<N) && (j<N) ) {
            char duplicateLetter = 0;

            // Increase j until we get a repeat
            while (j<N && !characters[s[j]]) {
                characters[s[j]] = true;
                j++;
            }
            maxCount = max(j-i, maxCount);

            if ( (j<N) && characters[s[j]] ) {
                duplicateLetter = s[j];
            }

            // Increase i until  duplicate letter erased
            // (could do until i==j but that is guaranteed to happen)
            bool duplicateErased = false;
            while (i<=j && (i<N) && !duplicateErased) {
                characters[s[i]] = false;
                if ( s[i] == duplicateLetter ) {
                    duplicateErased = true;
                }
                i++;
            }
            
            // go ahead and exit a bit early if maxCount
            // isn't going to increase
            if ( (j == N) && ((j-i) < maxCount)) {
                break;
            }
        }
        
        return maxCount;
        
    }
};


TEST(LongestSubstring, CorrectTest)
{
    Solution solution;
    ASSERT_EQ(solution.lengthOfLongestSubstring("abcabcbb"), 3);
    ASSERT_EQ(solution.lengthOfLongestSubstring(""), 0);
    ASSERT_EQ(solution.lengthOfLongestSubstring("z"), 1);
    ASSERT_EQ(solution.lengthOfLongestSubstring("thequickredfoxjumpedoverthebrownlazydog"), 13);
    ASSERT_EQ(solution.lengthOfLongestSubstring(" "), 1);
    ASSERT_EQ(solution.lengthOfLongestSubstring("This is a sentence."), 6);
}
