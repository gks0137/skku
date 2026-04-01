#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
    dp[0][0] = 1;
    dp[0][1] = 0;
    dp[1][0] = 1;
    dp[1][1] = 0;

    for (int i = 2; i <= n; ++i) {
        dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % 10007;
        dp[i][1] = (dp[i - 2][0] + dp[i - 2][1]) % 10007;
    }

    std::cout << (dp[n][0] + dp[n][1]) % 10007 << '\n';

    return 0;
}
