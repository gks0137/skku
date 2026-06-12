#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.length();
        int i = n - 1;
        
        // Skip trailing spaces
        while (i >= 0 && s[i] == ' ') {
            i--;
        }
        
        // Count the length of the last word
        int length = 0;
        while (i >= 0 && s[i] != ' ') {
            length++;
            i--;
        }
        
        return length;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    string s = "Hello World";
    cout << sol.lengthOfLastWord(s) << endl;




    return 0;
}