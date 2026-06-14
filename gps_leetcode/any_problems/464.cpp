#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (maxChoosableInteger >= desiredTotal) return true;
        if ((maxChoosableInteger + 1) * maxChoosableInteger / 2 < desiredTotal) return false;
        vector<int> dp(1 << maxChoosableInteger, -1);
        function<bool(int, int)> dfs = [&](int mask, int total) {
            if (dp[mask] != -1) return dp[mask];
            for (int i = 0; i < maxChoosableInteger; i++) {
                if ((mask & (1 << i)) == 0) {
                    if (total + i + 1 >= desiredTotal || !dfs(mask | (1 << i), total + i + 1)) {
                        return dp[mask] = true;
                    }
                }
            }
            return dp[mask] = false;
        };
        return dfs(0, 0);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    int maxChoosableInteger = 10, desiredTotal = 11;
    cout << sol.canIWin(maxChoosableInteger, desiredTotal) << "\n";




    return 0;
}