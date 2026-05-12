#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
string longestPalindrome(string s) {
    int longest = 0;
    string ans;

    for (int start = 0; start < (int)s.size(); start++) {
        for (int end = (int)s.size()-1; end >= start; end--) {
            if (s[start] == s[end]) {
                int left = start, right = end;
                while (left < right && s[left] == s[right]) {
                    left++;
                    right--;
                }
                if (left >= right) {
                    int len = end - start + 1;
                    if (len > longest) {
                        longest = len;
                        ans = s.substr(start, len);
                        break;
                    }
                }
            }
        }
    }
    return ans;
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