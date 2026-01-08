#include <bits/stdc++.h>
using namespace std;

const char AI = 'O';
const char HUMAN = 'X';
const char EMPTY = '_';

bool movesLeft(vector<vector<char>>& board) {
    for (auto &r : board)
        for (char c : r)
            if (c == EMPTY) return true;
    return false;
}

int evaluate(vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        // rows
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == AI) return 10;
            if (board[i][0] == HUMAN) return -10;
        }
        // columns
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            if (board[0][i] == AI) return 10;
            if (board[0][i] == HUMAN) return -10;
        }
    }

    // diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return 10;
        if (board[0][0] == HUMAN) return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return 10;
        if (board[0][2] == HUMAN) return -10;
    }

    return 0;
}

int minimax(vector<vector<char>>& board, bool isMax) {
    int score = evaluate(board);
    if (score != 0) return score;
    if (!movesLeft(board)) return 0;

    if (isMax) { // AI turn
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else { // Human turn
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    best = min(best, minimax(board, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int,int> bestMove(vector<vector<char>>& board, bool aiTurn) {
    int bestVal = aiTurn ? -1000 : 1000;
    pair<int,int> move = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = aiTurn ? AI : HUMAN;
                int val = minimax(board, !aiTurn);
                board[i][j] = EMPTY;

                if ((aiTurn && val > bestVal) ||
                    (!aiTurn && val < bestVal)) {
                    bestVal = val;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}

int main() {
    vector<vector<char>> board(3, vector<char>(3));
    int xCount = 0, oCount = 0;

    cout << "Enter board (3 lines):\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'X') xCount++;
            if (board[i][j] == 'O') oCount++;
        }
    }

    bool aiTurn = (oCount < xCount);  // O plays after X

    auto move = bestMove(board, aiTurn);

    if (move.first == -1)
        cout << "No valid moves (game over)\n";
    else
        cout << "Best move: Row " << move.first
             << ", Col " << move.second << endl;

    return 0;
}
