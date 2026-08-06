#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> count_t, count_cur;
        int n = s.size(), m = t.size();
        for (char c : t) {
            count_t[c]++;
        }
        int count = 0, left = 0, right = 0;
        int ans_left = 0, ans_len = INT_MAX;
        while (count < m && right < n) {
            char c = s[right];
            count_cur[c]++;
            if (count_t.count(c) && count_cur[c] <= count_t[c]) {
                count++;
            }
            right++;
        }
        while (count == m) {
            if (ans_len > right - left) {
                ans_len = right - left;
                ans_left = left;
            }
            char c = s[left];
            count_cur[c]--;
            if (count_t.count(c) && count_cur[c] < count_t[c]) {
                count--;
                while (count < m && right < n) {
                    char c = s[right];
                    count_cur[c]++;
                    if (count_t.count(c) && count_cur[c] <= count_t[c]) {
                        count++;
                    }
                    right++;
                }
            }
            left++;

        }

        return ans_len == INT_MAX ? "" : s.substr(ans_left, ans_len);
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    return 0;
}