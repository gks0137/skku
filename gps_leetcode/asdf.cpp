#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0) return INT_MAX;
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        return (long long) dividend / divisor;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int dividened = -7, divisor = 3;
    cout << sol.divide(dividened, divisor) << "\n";





    return 0;
}