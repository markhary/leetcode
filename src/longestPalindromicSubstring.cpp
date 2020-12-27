// https://leetcode.com/problems/longest-palindromic-substring
//
// Status: Accepted
// Runtime: 144 ms
// Score: 46.46%
//

#include <algorithm>
#include <string>
#include <list>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

class BruteForce
{
public:
  bool isPalimdrone(string s)
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

  string longestPalindrome(string s)
  {
    int n = s.length();

    if (n == 1)
      return s;

    // This is an O(n^3) solution. Brute force method works,
    // but is slow

    for (int p = 0; p < n; p++)
    {
      for (int i = 0; i <= p; i++)
      {
        string palindrome = s.substr(i, n - p);
        if (isPalimdrone(palindrome))
          return palindrome;
      }
    }

    return "";
  }
};

class Solution
{
public:
  struct substring
  {
    int first;
    int last;
  };

  string longestPalindrome(string s)
  {
    int n = s.length();

    if (n == 1)
    {
      return s;
    }

    list<substring> palindromes;

    // Centered substrings of a palindrome are also palindromes, therefore
    // find all small palindromes and grow them - list will get shorter
    int start = 0;
    int length = 1;

    // Find all of the palindromes of length 1 and 2
    for (int i = 0; i < n; i++)
    {
      palindromes.push_back(substring({i, i}));
      string candidate = s.substr(i, 1);
      if (((i + 1) < n) && (s[i] == s[i + 1]))
      {
        palindromes.push_back(substring({i, i + 1}));
        string candidate = s.substr(i, 2);
        if (2 > length)
        {
          start = i;
          length = 2;
        }
      }
    }

    while (!palindromes.empty())
    {
      palindromes.remove_if([&start, &length, &n, &s](auto &p) {
        if (((p.first - 1) >= 0) &&
            ((p.last + 1) < n) &&
            (s[p.first - 1] == s[p.last + 1]))
        {
          p.first--;
          p.last++;

          int l = p.last - p.first + 1;
          if (l > length)
          {
            start = p.first;
            length = l;
          }
          return false;
        }
        return true;
      });
    }

    return s.substr(start, length);
  }
};

TEST(LongestPalindromicSubstring, Empty)
{
  BruteForce brute;
  Solution solution;
  string word = "";
  string answer = "";

  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}

TEST(LongestPalindromicSubstring, SingleCharacter)
{
  BruteForce brute;
  Solution solution;
  string word = "a";
  string answer = "a";

  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}

TEST(LongestPalindromicSubstring, TwoCharacters)
{
  BruteForce brute;
  Solution solution;

  string word = "ac";
  string answer = "a";
  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}

TEST(LongestPalindromicSubstring, TwoCharactersEqual)
{
  BruteForce brute;
  Solution solution;

  string word = "bb";
  string answer = "bb";
  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}

TEST(LongestPalindromicSubstring, Example)
{
  BruteForce brute;
  Solution solution;
  string word = "babad";
  string answer = "bab";

  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}

TEST(LongestPalindromicSubstring, Test1)
{
  BruteForce brute;
  Solution solution;
  string word = "kyyrjtdplseovzwjkykrjwhxquwxsfsorjiumvxjhjmgeueafubtonhlerrgsgohfosqssmizcuqryqomsipovhhodpfyudtusjhonlqabhxfahfcjqxyckycstcqwxvicwkjeuboerkmjshfgiglceycmycadpnvoeaurqatesivajoqdilynbcihnidbizwkuaoegm";
  string answer = "kyk";

  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}

TEST(LongestPalindromicSubstring, Test2)
{
  BruteForce brute;
  Solution solution;
  string word = "zudfweormatjycujjirzjpyrmaxurectxrtqedmmgergwdvjmjtstdhcihacqnothgttgqfywcpgnuvwglvfiuxteopoyizgehkwuvvkqxbnufkcbodlhdmbqyghkojrgokpwdhtdrwmvdegwycecrgjvuexlguayzcammupgeskrvpthrmwqaqsdcgycdupykppiyhwzwcplivjnnvwhqkkxildtyjltklcokcrgqnnwzzeuqioyahqpuskkpbxhvzvqyhlegmoviogzwuiqahiouhnecjwysmtarjjdjqdrkljawzasriouuiqkcwwqsxifbndjmyprdozhwaoibpqrthpcjphgsfbeqrqqoqiqqdicvybzxhklehzzapbvcyleljawowluqgxxwlrymzojshlwkmzwpixgfjljkmwdtjeabgyrpbqyyykmoaqdambpkyyvukalbrzoyoufjqeftniddsfqnilxlplselqatdgjziphvrbokofvuerpsvqmzakbyzxtxvyanvjpfyvyiivqusfrsufjanmfibgrkwtiuoykiavpbqeyfsuteuxxjiyxvlvgmehycdvxdorpepmsinvmyzeqeiikajopqedyopirmhymozernxzaueljjrhcsofwyddkpnvcvzixdjknikyhzmstvbducjcoyoeoaqruuewclzqqqxzpgykrkygxnmlsrjudoaejxkipkgmcoqtxhelvsizgdwdyjwuumazxfstoaxeqqxoqezakdqjwpkrbldpcbbxexquqrznavcrprnydufsidakvrpuzgfisdxreldbqfizngtrilnbqboxwmwienlkmmiuifrvytukcqcpeqdwwucymgvyrektsnfijdcdoawbcwkkjkqwzffnuqituihjaklvthulmcjrhqcyzvekzqlxgddjoir";
  string answer = "gykrkyg";

  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}

TEST(LongestPalindromicSubstring, Test3)
{
  BruteForce brute;
  Solution solution;
  string word = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
  string answer = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";

  ASSERT_EQ(brute.longestPalindrome(word), answer);
  ASSERT_EQ(solution.longestPalindrome(word), answer);
}
