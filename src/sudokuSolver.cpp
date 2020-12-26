// https://leetcode.com/problems/sudoku-solver/
// Many of these methods come from validSudoku.cpp
//
// Status: Accepted
// Runtime: 84 ms
// Score: - 20.93%
//

#include <iostream>
#include <array>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

#define UNSOLVED '.'

struct Cell
{
    // Also keyed for N=9 and assuming numeric Sudoku
    int n;
    char value{UNSOLVED};
};

typedef vector<vector<char>> Chars;
typedef array<array<Cell, 9>, 9> Cells;

class Sudoku
{
public:
    // Only solve for N=9, but could expand generically
    Sudoku() : _R(3), _C(3), _solved(false)
    {
        _M = _R * _C;
        _N = _M * _M;
    }

    void display(Cells &board, bool code)
    {
        cout << (code ? "{" : "");
        for (int n = 0; n < _N; n++)
        {
            int r = n2r(n);
            int c = n2c(n);
            if (c == 0)
            {
                cout << (code ? "{" : "");
            }
            cout << (code ? "'" : "")
                 << board[r][c].value
                 << (code ? "'," : "")
                 << " ";
            if (c == (_M - 1))
            {
                cout << (code ? "}," : "");
                cout << endl;
            }
        }
        cout << (code ? "}" : "") << endl;
    }

    bool getCandidates(Cells &board, int r, int c, int &values)
    {
        try
        {
            int b = rc2b(r, c);

            int rowValues = 0;
            int columnValues = 0;
            int boxValues = 0;
            for (int i = 0; i < _M; i++)
            {
                checkRow(r, i, board, rowValues);
                checkColumn(i, c, board, columnValues);
                checkBox(b, i, board, boxValues);
            }
            values = (rowValues | columnValues | boxValues);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    void from(Chars &board)
    {
        for (int n = 0; n < _N; n++)
        {
            int r = n2r(n);
            int c = n2c(n);

            char value = board[r][c];
            _cells[r][c].n = n;
            _cells[r][c].value = value;
            if (value == UNSOLVED)
            {
                _unsolved.push_back(&_cells[r][c]);
            }
        }
    }

    void to(Chars &board)
    {
        for (int n = 0; n < _N; n++)
        {
            int r = n2r(n);
            int c = n2c(n);

            board[r][c] = _cells[r][c].value;
        }
    }

    void solve()
    {
        _cells = solve(_cells, _unsolved);
        _solved = true;
    }

    bool isSolved()
    {
        return _solved;
    }

    bool check()
    {
        vector<Cell *> unsolved = getUnsolved(_cells);
        return (unsolved.size() == 0);
    }

private:
    int n2r(int n)
    {
        return (n / _M);
    }

    int n2c(int n)
    {
        return (n % _M);
    }

    int rc2b(int r, int c)
    {
        return (r / _R) * _R + (c / _C);
    }

    Cells solve(Cells board, vector<Cell *> unsolved)
    {
        Cells b = board;

        for (auto &cell : unsolved)
        {
            int r = n2r(cell->n);
            int c = n2c(cell->n);

            int candidates = 0;
            if (!getCandidates(b, r, c, candidates))
            {
                return board;
            }

            for (int i = 1; i <= _M; i++)
            {
                if ((candidates & (1 << i)))
                {
                    continue;
                }
                b[r][c].value = 0x30 + i;

                int u = unsolved.size() - 1;
                if (u == 0)
                {
                    _solved = true;
                }
                else
                {
                    vector<Cell *> un(unsolved.begin() + 1, unsolved.end());
                    b = solve(b, un);
                }
                if (_solved)
                {
                    return b;
                }
            }
            return board;
        }

        return board;
    }

    vector<Cell *> getUnsolved(Cells &board)
    {
        vector<Cell *> unsolved;

        for (int n = 0; n < _N; n++)
        {
            int r = n2r(n);
            int c = n2c(n);
            if (board[r][c].value == UNSOLVED)
            {
                unsolved.push_back(&board[r][c]);
            }
        }

        return unsolved;
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

    bool checkRow(int row, int column, Cells &board, int &values)
    {
        checkValue(board[row][column].value, values);
        return true;
    }

    bool checkColumn(int row, int column, Cells &board, int &values)
    {
        checkValue(board[row][column].value, values);
        return true;
    }

    char getCell(int box, Cells &board, int i)
    {
        int firstRow = (box / _R) * _R;
        int firstCol = (box % _C) * _C;

        int row = firstRow + i / _R;
        int col = firstCol + (i % _C);

        return board[row][col].value;
    }

    bool checkBox(int box, int cell, Cells &board, int &values)
    {
        char c = getCell(box, board, cell);
        checkValue(c, values);
        return true;
    }

private:
    vector<Cell *> _unsolved;
    Cells _cells;
    int _R;
    int _C;
    int _M;
    int _N;
    bool _solved;
};

// class definition comes from leetcode
class Solution
{
public:
    void solveSudoku(Chars &board)
    {
        _sudoku.from(board);
        _sudoku.solve();
        _sudoku.to(board);
    }

    void display(Cells &board, bool code = false)
    {
        _sudoku.display(board, code);
    }

private:
    Sudoku _sudoku;
};

TEST(SudokuSolver, Solved)
{
    Sudoku sudoku;
    Chars board =
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
    Chars board =
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
    Chars board =
        {{'.', '3', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    Chars solved =
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
    Chars board =
        {{'.', '.', '4', '6', '7', '8', '9', '1', '2'},
         {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
         {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
         {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
         {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
         {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
         {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
         {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
         {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

    Chars solved =
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
    Chars board =
        {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
         {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
         {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
         {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
         {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
         {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
         {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
         {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
         {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    Chars solved =
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

TEST(SudokuSolver, Test1)
{
    Solution solution;
    Chars board =
        {{'.', '.', '.', '.', '.', '7', '.', '.', '9'},
         {'.', '4', '.', '.', '8', '1', '2', '.', '.'},
         {'.', '.', '.', '9', '.', '.', '.', '1', '.'},
         {'.', '.', '5', '3', '.', '.', '.', '7', '2'},
         {'2', '9', '3', '.', '.', '.', '.', '5', '.'},
         {'.', '.', '.', '.', '.', '5', '3', '.', '.'},
         {'8', '.', '.', '.', '2', '3', '.', '.', '.'},
         {'7', '.', '.', '.', '5', '.', '.', '4', '.'},
         {'5', '3', '1', '.', '7', '.', '.', '.', '.'}};

    Chars solved =
        {{'3', '1', '2', '5', '4', '7', '8', '6', '9'},
         {'9', '4', '7', '6', '8', '1', '2', '3', '5'},
         {'6', '5', '8', '9', '3', '2', '7', '1', '4'},
         {'1', '8', '5', '3', '6', '4', '9', '7', '2'},
         {'2', '9', '3', '7', '1', '8', '4', '5', '6'},
         {'4', '7', '6', '2', '9', '5', '3', '8', '1'},
         {'8', '6', '4', '1', '2', '3', '5', '9', '7'},
         {'7', '2', '9', '8', '5', '6', '1', '4', '3'},
         {'5', '3', '1', '4', '7', '9', '6', '2', '8'}};

    solution.solveSudoku(board);
    ASSERT_TRUE(board == solved);
}
