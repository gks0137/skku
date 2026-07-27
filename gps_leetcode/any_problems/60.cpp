#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = i + 1;
        }
        vector<int> fact(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        k--;
        string res = "";
        for (int i = n - 1; i >= 0; i--) {
            int idx = k / fact[i];
            res += to_string(nums[idx]);
            nums.erase(nums.begin() + idx);
            k %= fact[i];
        }
        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    int n = 3, k = 3;
    string ans = sol.getPermutation(n, k);
    cout << ans << endl; // Output: "213"



    return 0;
}