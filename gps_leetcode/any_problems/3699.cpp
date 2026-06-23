#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        r -= l;
        l = 0;

        vector<vector<int>> dp(n + 1, vector<int>(r, 0));
        for (int i = 0; i < r; i++) {
            dp[2][i] = i*2+2;
        }
        for (int i = 3; i <= n; i++) {
            int sum = 0;
            for (int j = 0; j < r; j++) {
                sum += dp[i - 1][r-j-1];
                sum %= 1000000007;
                dp[i][j] = sum;
            }
        }
        return accumulate(dp[n].begin(), dp[n].end(), 0LL) % 1000000007;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    int n = 3, l = 1, r = 3;
    cout << sol.zigZagArrays(n, l, r) << "\n";



    return 0;
}