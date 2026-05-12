#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int myAtoi(string s) {
        long long ans = 0;
        int sign = 1;
        int i = 0;
        while (i < s.size() && s[i] == ' ') {
            i++;
        }
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        while (i < s.size() && '0' <= s[i] && s[i] <= '9') {
            ans = ans * 10 + (s[i] - '0');
            if (ans > INT_MAX && sign == 1) {
                return INT_MAX;
            } else if (ans > (long long)INT_MAX + 1 && sign == -1) {
                return INT_MIN;
            }
            i++;
        }
        return sign * ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    string s = "-91283472332";
    cout << sol.myAtoi(s) << "\n";



    return 0;
}