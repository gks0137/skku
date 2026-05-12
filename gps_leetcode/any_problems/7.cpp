#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int reverse(int x) {
        int result = 0, sgn = x < 0 ? -1 : 1;
        long long xx = abs(x);
        while (xx != 0) {
            int digit = xx % 10;
            xx /= 10;
            if (result > (INT_MAX - digit) / 10) return 0;
            result = result * 10 + digit;
        }
        if (result > INT_MAX) return 0;
        return sgn * result;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int x = -123;
    cout << sol.reverse(x) << "\n";



    return 0;
}