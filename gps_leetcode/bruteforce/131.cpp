#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> partitions;
        // manacher's algorithm to find all palindromic substrings
        string t = "#";
        for (char c : s) {
            t += c;
            t += '#';
        }
        int m = t.size();
        vector<int> p(m, 0);
        int center = 0, right = 0;
        for (int i = 0; i < m; ++i) {
            int mirror = 2 * center - i;
            if (i < right) p[i] = min(right - i, p[mirror]);
            while (i + p[i] + 1 < m && i - p[i] - 1 >= 0 && t[i + p[i] + 1] == t[i - p[i] - 1]) {
                ++p[i];
            }
            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
            }
        }
        // backtracking to generate partitions
        vector<string> current;
        function<void(int)> backtrack = [&](int start) {
            if (start == n) {
                partitions.push_back(current);
                return;
            }
            for (int end = start; end < n; ++end) {
                int len = end - start + 1;
                int idx = start + end + 1; // index in the transformed string
                if (p[idx] >= len) {
                    current.push_back(s.substr(start, len));
                    backtrack(end + 1);
                    current.pop_back();
                }
            }
        };
        backtrack(0);
        return partitions;
        

    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    string s = "aab";
    vector<vector<string>> res = sol.partition(s);
    for (const auto& partition : res) {
        cout << "[";
        for (size_t i = 0; i < partition.size(); ++i) {
            cout << "\"" << partition[i] << "\"";
            if (i < partition.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }


    return 0;
}