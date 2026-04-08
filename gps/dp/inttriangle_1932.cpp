#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n;
    std::cin >> n;
    int size = (n*n + n)/2;
    vector<int> triangle(size + 1);
    vector<int>dp(n);

    for (int i = 1; i <= size; i++) {
        std::cin >> triangle[i];
        if (i >= size - n + 1) {
            dp[i - (size - n + 1)] = triangle[i];
        }
    }

    while (--n) {
        for (int i = 0; i < n; i++) {
            dp[i] = max(dp[i], dp[i + 1]) + triangle[n*(n-1)/2 + i + 1];
        }
    }
    std::cout << dp[0];




    return 0;
}
