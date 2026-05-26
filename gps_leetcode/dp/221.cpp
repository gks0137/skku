#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        if (n == 1) {
            for (char c : matrix[0]) {
                if (c == '1') return 1;
            }
            return 0;
        }
        if (m == 1) {
            for (int i = 0; i < n; i++) {
                if (matrix[i][0] == '1') return 1;
            }
            return 0;
        }
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int maxSide = 0;
        for (int i = 0; i < n; i++) {
            int num = matrix[i][0] - '0';
            dp[i][0] = num;
            maxSide = max(maxSide, num);
        }
        for (int j = 0; j < m; j++) {
            int num = matrix[0][j] - '0';
            dp[0][j] = num;
            maxSide = max(maxSide, num);
        }
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == '1') {
                    int side = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    dp[i][j] = side;
                    maxSide = max(maxSide, side);
                }
            }
        }
        return maxSide * maxSide;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    return 0;
}