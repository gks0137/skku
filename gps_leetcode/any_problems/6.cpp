#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        string ans;
        if (numRows == 1) {
            return s;
        }
        int n = s.size();
        for (int i = 0; i < numRows; i++) {
            int j = i;
            while (j < n) {
                ans += s[j];
                if (i != 0 && i != numRows - 1) {
                    int k = j + 2*(numRows - 1 - i);
                    if (k < n) {
                        ans += s[k];
                    }
                }
                j += 2 * numRows - 2;
            }
        }
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    string s = "paypalishiring";
    Solution sol;
    cout << sol.convert(s, 3) << "\n";



    return 0;
}