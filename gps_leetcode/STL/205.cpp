#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.length() != t.length()) {
            return false;
        }
        unordered_map<char, char> m1, m2;
        for (int i = 0; i < s.length(); i++) {
            char c1 = s[i], c2 = t[i];
            if (m1.find(c1) != m1.end()) {
                if (m1[c1] != c2) {
                    return false;
                }
            } else {
                m1[c1] = c2;
            }
            if (m2.find(c2) != m2.end()) {
                if (m2[c2] != c1) {
                    return false;
                }
            } else {
                m2[c2] = c1;
            }
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    string s = "bbbaaaba";
    string t = "aaabbbba";
    Solution sol;
    cout << sol.isIsomorphic(s, t) << "\n";



    return 0;
}