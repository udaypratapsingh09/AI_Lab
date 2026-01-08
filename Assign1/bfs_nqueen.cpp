#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

void bfsNQueen(int N) {
    queue<vector<int>> q;
    q.push({});

    while (!q.empty()) {
        vector<int> curr = q.front();
        q.pop();

        int row = curr.size();
        if (row == N) {
            for (int x : curr) cout << x << " ";
            cout << endl;
            continue;
        }

        for (int col = 0; col < N; col++) {
            if (isSafe(curr, row, col)) {
                vector<int> next = curr;
                next.push_back(col);
                q.push(next);
            }
        }
    }
}

int main() {
    int N;
    cout << "Enter N: ";
    cin >> N;
    bfsNQueen(N);
    return 0;
}
