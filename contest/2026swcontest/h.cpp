#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> dp(n+1, vector<int>(4, 0));
    dp[1][0] = 1;
    dp[1][3] = 1;
    dp[2][0] = dp[2][1] = dp[2][2] = dp[2][3] = 1;

    for (int i = (n%2==0 ? 4 : 3); i <= n; i+=2) {
        dp[i][0] = (dp[i-2][2] + dp[i-2][3]) % 1000000007;
        dp[i][1] = ((long long)dp[i-2][0] + dp[i-2][1] + dp[i-2][2]) % 1000000007;
        dp[i][2] = ((long long)dp[i-2][1] + dp[i-2][2] + dp[i-2][3]) % 1000000007;
        dp[i][3] = (dp[i-2][0] + dp[i-2][1]) % 1000000007;
    }

    cout << ((long long)dp[n][0] + dp[n][1] + dp[n][2] + dp[n][3]) % 1000000007;


    return 0;
}