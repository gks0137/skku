#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        string prefix = "";
        for (size_t i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];
            for (size_t j = 1; j < strs.size(); ++j) {
                if (i >= strs[j].size() || strs[j][i] != c) {
                    return prefix;
                }
            }
            prefix += c;
        }
        return prefix;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<string> strs = {"flower", "flow", "flight"};
    cout << sol.longestCommonPrefix(strs) << "\n";



    return 0;
}