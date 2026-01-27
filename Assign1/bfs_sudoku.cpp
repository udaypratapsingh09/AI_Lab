#include <bits/stdc++.h>
using namespace std;

using Board = vector<vector<char>>;

// Check if placing ch at (row, col) is valid
bool isValid(const Board &board, int row, int col, char ch) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == ch) return false; // row
        if (board[i][col] == ch) return false; // column
    }

    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[boxRow + i][boxCol + j] == ch)
                return false;

    return true;
}

// Check if board is complete
bool isSolved(const Board &board) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (board[i][j] == '.')
                return false;
    return true;
}

// BFS Sudoku Solver
bool solveSudokuBFS(Board &board) {
    queue<Board> q;
    q.push(board);

    while (!q.empty()) {
        Board curr = q.front();
        q.pop();

        if (isSolved(curr)) {
            board = curr;
            return true;
        }

        // find first empty cell
        int row = -1, col = -1;
        bool found = false;
        for (int i = 0; i < 9 && !found; i++) {
            for (int j = 0; j < 9; j++) {
                if (curr[i][j] == '.') {
                    row = i;
                    col = j;
                    found = true;
                    break;
                }
            }
        }

        // try all digits
        for (char ch = '1'; ch <= '9'; ch++) {
            if (isValid(curr, row, col, ch)) {
                Board next = curr;
                next[row][col] = ch;
                q.push(next);
            }
        }
    }
    return false;
}

// Helper to print board
void printBoard(const Board &board) {
    for (auto &row : board) {
        for (char c : row)
            cout << c << " ";
        cout << "\n";
    }
}

int main() {
    Board board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };

    if (solveSudokuBFS(board)) {
        cout << "Solved Sudoku:\n";
        printBoard(board);
    } else {
        cout << "No solution found.\n";
    }
}
