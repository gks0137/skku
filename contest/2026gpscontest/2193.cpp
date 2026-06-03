
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int abs(int a) {
    if (a < 0) return -a;
    return a;
}


class Solution {
public:
    int func(string& s, char c, int start, int end) {
        int l, r;
        for (int i = start; i <= end; i++) {
            if (s[i] == c) {
                l = i;
                break;
            }
        }
        for (int i = end; i >= start; i--) {
            if (s[i] == c) {
                r = i;
                break;
            }
        }
        if (l == r) {
            return -1;
        } else {
            if (l+r+1 == s.length()) return 0;
            int ret = abs((int)s.length()-1-l-r);
            int sstart = (((int)s.length()-1-l < r) ? (int)s.length()-1-l : r);
            char temp = s[sstart];
            for (int i = 0; i < ret; i++) {
                s[sstart+i] =  s[sstart+i+1];
            }
            s[sstart+ret] = temp;
            return ret;
        }
    }
    
    int minMovesToMakePalindrome(string s) {
        string ss(s.begin(), s.end());
        int l = 0, r = ss.size()-1;
        int ans = 0;
        while (l < r) {
            int plus = func(ss, ss[l], l, r);
            if (plus >= 0) {
                ans += plus;
            } else {
                string sss = s.substr(l + 1, r - l);
                return (abs((int)s.length()/2 - l) + minMovesToMakePalindrome(sss));
            }
            l++;r--;
        }
        return ans;
    }
};





int main()
{
    Solution sol;
    
    string s = "abba";
    cout << sol.minMovesToMakePalindrome(s);

    return 0;
}