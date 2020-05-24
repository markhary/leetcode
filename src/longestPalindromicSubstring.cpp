// https://leetcode.com/problems/longest-palindromic-substring
//
// Status: Time limit exceeded
// Runtime: -
// Score: -
//

#include <algorithm>
#include <string>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

class Solution
{
public:
  bool isPalindromicSubstring(string s)
  {
    int n = s.length();
    int m = n / 2;

    // check outside-in
    for (int i = 0; i < m; i++)
    {
      if (s[i] != s[n - i - 1])
        return false;
    }

    return true;
  }

  // This is an O(n^3) solution. Brute force method works,
  // but is slow
  string longestPalindromicSubstring(string s)
  {
    int n = s.length();

    if (n == 1)
      return s;

    for (int p = 0; p < n; p++)
    {
      for (int i = 0; i <= p; i++)
      {
        string palindrome = s.substr(i, n - p);
        if (isPalindromicSubstring(palindrome))
          return palindrome;
      }
    }

    return "";
  }
};

TEST(LongestPalindromicSubstring, CorrectSample)
{
  Solution solution;

  ASSERT_EQ(solution.longestPalindromicSubstring("babad"), "bab");
}

TEST(LongestPalindromicSubstring, Empty)
{
  Solution solution;

  ASSERT_EQ(solution.longestPalindromicSubstring(""), "");
}

TEST(LongestPalindromicSubstring, SingleCharacter)
{
  Solution solution;

  ASSERT_EQ(solution.longestPalindromicSubstring("a"), "a");
}

TEST(LongestPalindromicSubstring, TwoCharacters)
{
  Solution solution;

  ASSERT_EQ(solution.longestPalindromicSubstring("ac"), "a");
  ASSERT_EQ(solution.longestPalindromicSubstring("bb"), "bb");
}

TEST(LongestPalindromicSubstring, LongTest)
{
  Solution solution;
  string s = "kyyrjtdplseovzwjkykrjwhxquwxsfsorjiumvxjhjmgeueafubtonhlerrgsgohfosqssmizcuqryqomsipovhhodpfyudtusjhonlqabhxfahfcjqxyckycstcqwxvicwkjeuboerkmjshfgiglceycmycadpnvoeaurqatesivajoqdilynbcihnidbizwkuaoegm";

  ASSERT_EQ(solution.longestPalindromicSubstring(s), "kyk");
}