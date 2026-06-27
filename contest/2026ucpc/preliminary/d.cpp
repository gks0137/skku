#include <bits/stdc++.h>
#define LL_MAX 0x7fffffffffffffffLL
using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }
    sort(vals.begin(), vals.end(), [](const int& a, const int& b){return a > b;});

    for (int i = 0, j = vals.size()-1; i < j; i++, j--) {
        vals[i] -= vals[j];
    }

    n /= 2;
    vector<vector<long long>> dp(n, vector<long long>(2, LONG_LONG_MAX));
    dp[0][0] = vals[0];

    for (int i = 1; i < n; i++) {
        dp[i][0] = min(dp[i-1][0], dp[i-1][1]) + vals[i];
        dp[i][1] = dp[i-1][0] - vals[i];
    }
    cout << min(dp[n-1][0], dp[n-1][1]);




    return 0;
}