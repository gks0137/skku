#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int longestValidParentheses(string s) {
        deque<int> st;
        int max_len = 0, prev_len = 0;
        for (char c : s) {
            if (c == '(') {
                st.push_back(0);
            } else {
                if (!st.empty()) {
                    int len = 2;
                    if (st.back() > 0) {
                        len += st.back();
                        st.pop_back();
                    }
                    st.pop_back();
                    if (!st.empty()) {
                        if (st.back() > 0) {
                            st.back() += len;
                            max_len = max(max_len, st.back());
                        } else {
                            st.push_back(len);
                            max_len = max(max_len, len);
                        }
                    } else {
                        prev_len += len;
                        max_len = max(max_len, prev_len);
                    }
                } else {
                    prev_len = 0;
                }
            }
        }
        return max_len;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    string s[] = {"(()", ")()())", "", "(())(", "(()((((()", "()(()", "(()()"};
    int answer[] = {2, 4, 0, 4, 2, 2, 4};
    for (int t = 0; t < 7; t++) {
        cout << s[t] << ": " << sol.longestValidParentheses(s[t]) << ' ' << answer[t] << '\n';
    }

    return 0;
}