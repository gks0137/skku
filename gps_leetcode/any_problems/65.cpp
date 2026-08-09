#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    bool is_dot(char c) {
        return c == '.';
    }

    bool is_decimal(char c) {
        return c >= '0' && c <= '9';
    }

    bool is_exponential(char c) {
        return c == 'e' || c == 'E';
    }

    bool is_sign(char c) {
        return c == '+' || c == '-';
    }


    bool isNumber(string s) {
        int n = s.size();
        int i = 0;
        if (i < n && is_sign(s[i])) {
            i++;
        }
        bool has_dot = false;
        bool has_exp = false;
        bool has_num = false;
        for (; i < n; i++) {
            if (is_decimal(s[i])) {
                has_num = true;
            } else if (is_dot(s[i])) {
                if (has_dot || has_exp) {
                    return false;
                }
                has_dot = true;
            } else if (is_exponential(s[i])) {
                if (has_exp || !has_num) {
                    return false;
                }
                has_exp = true;
                has_num = false;
                if (i + 1 < n && is_sign(s[i + 1])) {
                    i++;
                }
            } else {
                return false;
            }
        }
        return has_num;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    int n = 3, k = 3;
    string ans = sol.getPermutation(n, k);
    cout << ans << endl; // Output: "213"



    return 0;
}