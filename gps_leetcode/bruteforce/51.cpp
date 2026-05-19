

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;

        vector<int> cur_queens;
        vector<string> cur_board(n, string(n, '.'));
        function<void(int, vector<int>&)> backtrack = [&](int row, vector<int>& queens_col) {
            if (row == n) {
                solutions.push_back(cur_board);
                return;
            }
            for (int col = 0; col < n; ++col) {
                bool valid = true;
                for (int i = 0; i < queens_col.size(); ++i) {
                    if (queens_col[i] == col || abs(queens_col[i] - col) == abs(i - row)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    queens_col.push_back(col);
                    cur_board[row][col] = 'Q';
                    backtrack(row + 1, queens_col);
                    cur_board[row][col] = '.';
                    queens_col.pop_back();
                }
            }
        };
        backtrack(0, cur_queens);
        return solutions;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int n = 13;
    vector<vector<string>> res = sol.solveNQueens(n);
    cout << res.size() << " solutions for " << n << "-Queens:\n";


    return 0;
}