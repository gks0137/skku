#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int s_idx = s.size()-1, p_idx = p.size()-1;
        while (s_idx >= 0 && p_idx >= 0) {
            if (p[p_idx] == '*') {
                if (p_idx-1 < 0) return false;
                char c = p[p_idx-1];
                if (c == '.') {
                    for (int i = s_idx; i >= -1; i--) {
                        if (isMatch(s.substr(0, i+1), p.substr(0, p_idx-1))) {
                            return true;
                        }
                    }
                    return false;
                }
                // not .
                while (s_idx >= 0 && s[s_idx] == c) {
                    if (isMatch(s.substr(0, s_idx+1), p.substr(0, p_idx-1))) {
                        return true;
                    }
                    s_idx--;
                }
                p_idx -= 2;
            } else {
                if (s[s_idx] != p[p_idx] && p[p_idx] != '.') return false;
                s_idx--;
                p_idx--;
            }
        }
        if (s_idx >= 0) return false;
        while (p_idx >= 0) {
            if (p[p_idx] == '*') {
                p_idx -= 2;
            } else {
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


    string s = "aaa", p = "ab*a*c*a";
    cout << sol.isMatch(s, p) << "\n";



    return 0;
}