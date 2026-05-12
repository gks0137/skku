#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        // Manacher's algorithm
        string t = "#";
        for (char c : s) {
            t += c;
            t += '#';
        }
        int n = (int)t.size();
        vector<int> p(n);
        int c = 0, r = 0;
        for (int i = 0; i < n; i++) {
            int k = (i > r) ? 1 : min(p[2 * c - i], r - i + 1);
            while (i - k >= 0 && i + k < n && t[i - k] == t[i + k]) {
                k++;
            }
            p[i] = k;
            if (i + k - 1 > r) {
                c = i;
                r = i + k - 1;
            }
        }
        int maxLen = *max_element(p.begin(), p.end());
        int centerIndex = find(p.begin(), p.end(), maxLen) - p.begin();
        return s.substr((centerIndex - maxLen + 1) / 2, maxLen - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    string s = "a";
    Solution sol;
    cout << sol.longestPalindrome(s) << "\n";



    return 0;
}