// https://leetcode.com/problems/valid-sudoku/
//
// Status: Accepted
// Runtime: 36 ms
// Score: 65.51 %
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

// class definition comes from leetcode
class Solution
{
public:
    int getVal(char c)
    {
        if (c == '.')
        {
            return 0;
        }
        return c - 0x30;
    }

    void checkValue(char c, int &values)
    {
        int v = getVal(c);
        if (!v)
        {
            return;
        }
        if (values & (1 << v))
        {
            throw runtime_error("invalid");
        }
        values |= (1 << v);
    }

    bool checkRow(int row, vector<vector<char>> &board)
    {
        int values = 0;
        for (int i = 0; i < 9; i++)
        {
            checkValue(board[row][i], values);
        }
        return true;
    }

    bool checkColumn(int column, vector<vector<char>> &board)
    {
        int values = 0;
        for (int i = 0; i < 9; i++)
        {
            checkValue(board[i][column], values);
        }
        return true;
    }

    char getCell(int box, int i, vector<vector<char>> &board)
    {
        int firstRow = (box / 3) * 3;
        int firstCol = (box % 3) * 3;

        int row = firstRow + i / 3;
        int col = firstCol + (i % 3);

        return board[row][col];
    }

    bool checkBox(int box, vector<vector<char>> &board)
    {
        int values = 0;
        for (int i = 0; i < 9; i++)
        {
            char c = getCell(box, i, board);
            checkValue(c, values);
        }
        return true;
    }

    bool isValidSudoku(vector<vector<char>> &board)
    {
        try
        {
            for (int i = 0; i < 9; i++)
            {
                checkRow(i, board);
                checkColumn(i, board);
                checkBox(i, board);
            }
        }
        catch (...)
        {
            return false;
        }
        return true;
    }
};

TEST(ValidSudoku, Valid)
{
    Solution solution;
    vector<vector<char>> board =
        {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
         {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
         {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
         {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
         {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
         {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
         {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
         {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
         {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    ASSERT_EQ(solution.isValidSudoku(board), true);
}

TEST(ValidSudoku, Invalid)
{
    Solution solution;
    vector<vector<char>> board =
        {{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
         {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
         {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
         {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
         {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
         {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
         {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
         {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
         {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    ASSERT_EQ(solution.isValidSudoku(board), false);
}
