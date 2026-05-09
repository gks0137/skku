#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> charIndex;
        int maxLength = 0, start = 0;

        for (int end = 0; end < s.size(); end++) {
            if (charIndex.find(s[end]) != charIndex.end() && charIndex[s[end]] >= start) {
                start = charIndex[s[end]] + 1;
            }
            charIndex[s[end]] = end;
            maxLength = max(maxLength, end - start + 1);
            // cout << "Current character: " << s[end] << ", Start: " << start << ", End: " << end << ", Max Length: " << maxLength << "\n";
        }
        return maxLength;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    string s = "abba";
    Solution sol;
    cout << sol.lengthOfLongestSubstring(s) << "\n";



    return 0;
}