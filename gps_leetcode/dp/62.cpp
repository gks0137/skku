#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        long long ans = 1, a, b;
        b = m +n  - 2;
        if (m > n) {
            a = n - 1;
        } else {
            a = m - 1;
        }
        for (int i = b-a+1; i <= b; i++) {
            ans = ans * i / (i - b + a) ;
        }
        
        return ans;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    int m = 3, n = 7;
    cout << sol.uniquePaths(m, n) << "\n";



    return 0;
}