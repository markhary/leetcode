// https://leetcode.com/problems/sudoku-solver/
// Many of these methods come from validSudoku.cpp
//
// Status: In progress
// Runtime: - ms
// Score: - %
//

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

struct Cell
{
    char value{'.'};
    // Also keyed for N=9 only
    vector<char> candidates{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
};

class Sudoku
{
public:
    // Only solve for N=9, but could expand generically
    Sudoku() : _R(3), _C(3)
    {
        _N = _R * _C;
        _cells = vector<vector<Cell>>(_N, vector<Cell>(_N));
    }

    bool isValid()
    {
        try
        {
            // optimized by iterating only once through all three in two loops
            for (int i = 0; i < _N; i++)
            {
                int rowValues = 0;
                int columnValues = 0;
                int boxValues = 0;
                for (int j = 0; j < _N; j++)
                {
                    checkRow(i, j, rowValues);
                    checkColumn(j, i, columnValues); // row and column switched
                    checkBox(i, j, boxValues);
                }
            }
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    void from(vector<vector<char>> &board)
    {
        for (int r = 0; r < _N; r++)
        {
            for (int c = 0; c < _N; c++)
            {
                char value = board[r][c];
                _cells[r][c].value = value;
                if (value != '.')
                {
                    _cells[r][c].candidates.clear();
                }
            }
        }
    }

    void to(vector<vector<char>> &board)
    {
        for (int r = 0; r < _N; r++)
        {
            for (int c = 0; c < _N; c++)
            {
                board[r][c] = _cells[r][c].value;
            }
        }
    }

    void solve()
    {
    }

private:
    int getVal(char c)
    {
        if (c == '.')
        {
            return 0;
        }
        return c - '0';
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

    bool checkRow(int row, int column, int &values)
    {
        checkValue(_cells[row][column].value, values);
        return true;
    }

    bool checkColumn(int row, int column, int &values)
    {
        checkValue(_cells[row][column].value, values);
        return true;
    }

    char getCell(int box, int i)
    {
        int firstRow = (box / _R) * _R;
        int firstCol = (box % _C) * _C;

        int row = firstRow + i / _R;
        int col = firstCol + (i % _C);

        return _cells[row][col].value;
    }

    bool checkBox(int box, int cell, int &values)
    {
        char c = getCell(box, cell);
        checkValue(c, values);
        return true;
    }

private:
    vector<vector<Cell>> _cells;
    int _R;
    int _C;
    int _N;
};

// class definition comes from leetcode
class Solution
{
public:
    void solveSudoku(vector<vector<char>> &board)
    {
        _sudoku.from(board);
        _sudoku.solve();
        _sudoku.to(board);
    }

private:
    Sudoku _sudoku;
};

TEST(SudokuSolver, Example)
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

    vector<vector<char>> solved =
        {{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'.', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    solution.solveSudoku(board);
    ASSERT_TRUE(board == solved);
}

TEST(SudokuSolver, Valid)
{
    Sudoku sudoku;
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

    sudoku.from(board);
    ASSERT_EQ(sudoku.isValid(), true);
}

TEST(SudokuSolver, Invalid)
{
    Sudoku sudoku;
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

    sudoku.from(board);
    ASSERT_EQ(sudoku.isValid(), false);
}
