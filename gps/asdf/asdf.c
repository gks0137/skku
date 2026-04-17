#include <stdio.h>


int main() {
    int a;

    scanf("%d", &a);

    int dp[3] = {0, 1, 1};
    for (int i = 3; i <= a; i++) {
        dp[2] = dp[0] + dp[1];
        dp[0] = dp[1];
        dp[1] = dp[2];
    }

    printf("%d\n", dp[2]);

    

    return 0;
}