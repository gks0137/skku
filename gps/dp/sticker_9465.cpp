#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        vector<vector<int>> sticker(2, vector<int>(n));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                std::cin >> sticker[i][j];
            }
        }
        // up, down, none
        vector<vector<int>> dp(3, vector<int>(n));
        dp[0][0] = sticker[0][0];
        dp[1][0] = sticker[1][0];
        for (int i = 1; i < n; i++) {
            dp[0][i] = max(dp[1][i-1], dp[2][i-1]) + sticker[0][i];
            dp[1][i] = max(dp[0][i-1], dp[2][i-1]) + sticker[1][i];
            dp[2][i] = max(dp[0][i-1], max(dp[1][i-1], dp[2][i-1]));
        }
        std::cout << max(dp[0][n-1], max(dp[1][n-1], dp[2][n-1])) << "\n";

    }

    

    return 0;
}
