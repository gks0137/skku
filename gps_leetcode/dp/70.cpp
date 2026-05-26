#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int n = 5;
    cout << sol.climbStairs(n) << "\n";



    return 0;
}