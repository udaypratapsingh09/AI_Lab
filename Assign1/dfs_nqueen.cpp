#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> board;

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

void dfsNQueen(int row) {
    if (row == N) {
        for (int i = 0; i < N; i++)
            cout << board[i] << " ";
        cout << endl;
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            dfsNQueen(row + 1);
        }
    }
}

int main() {
    cout << "Enter N: ";
    cin >> N;
    board.resize(N);
    dfsNQueen(0);
    return 0;
}
