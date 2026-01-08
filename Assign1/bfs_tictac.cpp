#include <bits/stdc++.h>
using namespace std;

const char AI = 'O';
const char HUMAN = 'X';
const char EMPTY = '_';

struct State {
    string board;
    char turn;
};

int evaluate(const string &b) {
    int wins[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto &w : wins) {
        if (b[w[0]] == b[w[1]] && b[w[1]] == b[w[2]]) {
            if (b[w[0]] == AI) return 10;
            if (b[w[0]] == HUMAN) return -10;
        }
    }
    return 0;
}

bool movesLeft(const string &b) {
    return b.find(EMPTY) != string::npos;
}

vector<string> nextStates(const string &b, char turn) {
    vector<string> states;
    for (int i = 0; i < 9; i++) {
        if (b[i] == EMPTY) {
            string nb = b;
            nb[i] = turn;
            states.push_back(nb);
        }
    }
    return states;
}

int main() {
    string start = "_________"; // empty board
    char startTurn = AI;

    unordered_map<string, int> value;
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> outdeg;

    queue<State> q;
    q.push({start, startTurn});

    // BFS: build game graph
    while (!q.empty()) {
        auto [b, turn] = q.front(); q.pop();
        if (graph.count(b)) continue;

        int score = evaluate(b);
        if (score != 0 || !movesLeft(b)) {
            value[b] = score;
            continue;
        }

        vector<string> children = nextStates(b, turn);
        graph[b] = children;
        outdeg[b] = children.size();

        for (auto &c : children)
            q.push({c, turn == AI ? HUMAN : AI});
    }

    // Reverse graph
    unordered_map<string, vector<string>> parent;
    for (auto &[p, childs] : graph)
        for (auto &c : childs)
            parent[c].push_back(p);

    queue<string> rq;
    for (auto &[s, v] : value)
        rq.push(s);

    // Retrograde BFS (minimax propagation)
    while (!rq.empty()) {
        string cur = rq.front(); rq.pop();

        for (auto &p : parent[cur]) {
            if (value.count(p)) continue;

            char turn = (count(p.begin(), p.end(), AI) ==
                         count(p.begin(), p.end(), HUMAN)) ? AI : HUMAN;

            if (turn == AI)
                value[p] = -1000;
            else
                value[p] = 1000;

            for (auto &c : graph[p]) {
                if (!value.count(c)) {
                    value.erase(p);
                    break;
                }
                if (turn == AI)
                    value[p] = max(value[p], value[c]);
                else
                    value[p] = min(value[p], value[c]);
            }

            if (value.count(p))
                rq.push(p);
        }
    }

    // Find best move
    int best = -1000;
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (start[i] == EMPTY) {
            string nb = start;
            nb[i] = AI;
            if (value[nb] > best) {
                best = value[nb];
                bestMove = i;
            }
        }
    }

    cout << "Best move index (0–8): " << bestMove << endl;
    return 0;
}
