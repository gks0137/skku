#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        string digits(10, 0);
        int idx = 0;
        while (x > 0) {
            digits[idx++] = x % 10;
            x /= 10;
        }
        for (int i = 0; i < idx / 2; i++) {
            if (digits[i] != digits[idx - 1 - i]) {
                return false;
            }
        }
        return true;

    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int x = 121;
    cout << sol.isPalindrome(x) << "\n";



    return 0;
}