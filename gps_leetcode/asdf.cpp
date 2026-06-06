#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1.0;
        long long nn = n;
        if (nn < 0) {
            nn = -nn;
            x = 1 / x;
        }
        while (nn > 0) {
            if (nn % 2 == 1) {
                ans *= x;
            }
            x *= x;
            nn /= 2;
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    double x = 2.00000;
    int n = 10;
    cout << sol.myPow(x, n) << "\n";
    
    return 0;
}