#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        function<bool(int, int)> backtrack = [&](int r, int c) {
            if (r == 9) return true;
            if (c == 9) return backtrack(r + 1, 0);
            if (board[r][c] != '.') return backtrack(r, c + 1);
            for (char num = '1'; num <= '9'; num++) {
                bool valid = true;
                for (int i = 0; i < 9; i++) {
                    if (board[r][i] == num || board[i][c] == num || board[3 * (r / 3) + i / 3][3 * (c / 3) + i % 3] == num) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) continue;
                board[r][c] = num;
                if (backtrack(r, c + 1)) return true;
                board[r][c] = '.';
            }
            return false;
        };
        backtrack(0, 0);
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;



    return 0;
}