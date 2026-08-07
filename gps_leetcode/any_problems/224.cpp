#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int calculate(string s) {
        stack<long long> st;
        long long num = 0, sign = 1, result = 0; // to handle INT_MIN cases
        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            } else if (c == '+') {
                result += sign * num;
                num = 0;
                sign = 1;
            } else if (c == '-') {
                result += sign * num;
                num = 0;
                sign = -1;
            } else if (c == '(') {
                st.push(result);
                st.push(sign);
                result = 0;
                sign = 1;
            } else if (c == ')') {
                result += sign * num;
                num = 0;
                result *= st.top(); st.pop();
                result += st.top(); st.pop();
            }
        }
        return result + sign * num;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    string s = "3+(2 - 2)"; // input contains only digits, '+', '-', '(', ')', and ' ' characters
    cout << sol.calculate(s) << "\n";




    return 0;
}