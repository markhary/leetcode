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

#define UNSOLVED '.'

struct Cell
{
    // Also keyed for N=9 and assuming numeric Sudoku
    vector<char> candidates{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int row;
    int column;
};

class Sudoku
{
public:
    // Only solve for N=9, but could expand generically
    Sudoku() : _R(3), _C(3), _solved(false)
    {
        _N = _R * _C;
        _cells = vector<vector<Cell>>(_N, vector<Cell>(_N));
    }

    void display(vector<vector<char>> board)
    {
        for (int r = 0; r < _N; r++)
        {
            for (int c = 0; c < _N; c++)
            {
                cout << board[r][c] << " ";
            }
            cout << endl;
        }
    }

    bool isValid(vector<vector<char>> board)
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
                    checkRow(i, j, board, rowValues);
                    checkColumn(j, i, board, columnValues); // row and column switched
                    checkBox(i, j, board, boxValues);
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
        _board = board;
        for (int r = 0; r < _N; r++)
        {
            for (int c = 0; c < _N; c++)
            {
                char value = board[r][c];
                _cells[r][c].row = r;
                _cells[r][c].column = c;
                if (value != UNSOLVED)
                {
                    _cells[r][c].candidates.clear();
                }
            }
        }
    }

    void to(vector<vector<char>> &board)
    {
        board = _board;
    }

    void solve()
    {
        _board = solve(_board);
        _solved = true;
    }

    bool isSolved()
    {
        return _solved;
    }

    bool check()
    {
        return check(_board);
    }

private:
    vector<vector<char>> solve(vector<vector<char>> board)
    {
        vector<vector<char>> b = board;

        for (int r = 0; r < _N; r++)
        {
            for (int c = 0; c < _N; c++)
            {
                if (b[r][c] != UNSOLVED)
                {
                    continue;
                }

                for (int i = 0; i < _N; i++)
                {
                    b[r][c] = 0x31 + i;
                    if (isValid(b))
                    {
                        if (check(b))
                        {
                            return b;
                        }
                        else
                        {
                            b = solve(b);
                            if (check(b))
                            {
                                return b;
                            }
                        }
                    }
                }
            }
        }

        return board;
    }

    bool check(vector<vector<char>> &board)
    {
        for (int r = 0; r < _N; r++)
        {
            for (int c = 0; c < _N; c++)
            {
                if (board[r][c] == UNSOLVED)
                {
                    return false;
                }
            }
        }
        return true;
    }

    int getVal(char c)
    {
        if (c == UNSOLVED)
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

    bool checkRow(int row, int column, vector<vector<char>> &board, int &values)
    {
        checkValue(board[row][column], values);
        return true;
    }

    bool checkColumn(int row, int column, vector<vector<char>> &board, int &values)
    {
        checkValue(board[row][column], values);
        return true;
    }

    char getCell(int box, vector<vector<char>> &board, int i)
    {
        int firstRow = (box / _R) * _R;
        int firstCol = (box % _C) * _C;

        int row = firstRow + i / _R;
        int col = firstCol + (i % _C);

        return board[row][col];
    }

    bool checkBox(int box, int cell, vector<vector<char>> &board, int &values)
    {
        char c = getCell(box, board, cell);
        checkValue(c, values);
        return true;
    }

private:
    vector<vector<char>> _board;
    vector<vector<Cell>> _cells;
    int _R;
    int _C;
    int _N;
    bool _solved;
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

    void display(vector<vector<char>> &board)
    {
        _sudoku.display(board);
    }

private:
    Sudoku _sudoku;
};

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
    ASSERT_EQ(sudoku.isValid(board), true);
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
    ASSERT_EQ(sudoku.isValid(board), false);
}

TEST(SudokuSolver, Solved)
{
    Sudoku sudoku;
    vector<vector<char>> board =
        {{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    sudoku.from(board);
    ASSERT_EQ(sudoku.check(), true);
}

TEST(SudokuSolver, NotSolved)
{
    Sudoku sudoku;
    vector<vector<char>> board =
        {{'.', '3', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    sudoku.from(board);
    ASSERT_EQ(sudoku.check(), false);
}

TEST(SudokuSolver, Simple)
{
    Solution solution;
    vector<vector<char>> board =
        {{'.', '3', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    vector<vector<char>> solved =
        {{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    solution.solveSudoku(board);
    ASSERT_TRUE(board == solved);
}

TEST(SudokuSolver, TooSimple)
{
    Solution solution;
    vector<vector<char>> board =
        {{'.', '.', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    vector<vector<char>> solved =
        {{'5', '3', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    solution.solveSudoku(board);
    ASSERT_TRUE(board == solved);
}

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
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    solution.solveSudoku(board);
    ASSERT_TRUE(board == solved);
}