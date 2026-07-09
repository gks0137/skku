#include <bits/stdc++.h>
using namespace std;




class Solution {
public:
    string board2String(vector<vector<int>>& board) {
        string res;
        for (auto &row : board) {
            for (auto &cell : row) {
                res += to_string(cell);
            }
        }
        return res;
    }

    vector<vector<int>> string2Board(const string &s) {
        vector<vector<int>> board(2, vector<int>(3));
        for (int i = 0; i < 6; ++i) {
            board[i / 3][i % 3] = s[i] - '0';
        }
        return board;
    }

    int slidingPuzzle(vector<vector<int>>& board) {
        unordered_map<string, int> dist;

        dist[board2String(board)] = 0;

        queue<string> q;
        q.push(board2String(board));

        while (!q.empty()) {
            string cur = q.front();
            q.pop();

            if (cur == "123450") return dist[cur];

            int zeroPos = cur.find('0');
            int x = zeroPos / 3, y = zeroPos % 3;

            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (auto [dx, dy] : directions) {
                int newX = x + dx, newY = y + dy;
                if (newX >= 0 && newX < 2 && newY >= 0 && newY < 3) {
                    string next = cur;
                    swap(next[zeroPos], next[newX * 3 + newY]);
                    if (!dist.count(next)) {
                        dist[next] = dist[cur] + 1;
                        q.push(next);
                    }
                }
            }
        }
        return -1;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    return 0;
}