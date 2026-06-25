#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        vector<bool> dp(10001, 0);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) return false;
        sum /= 2;
        dp[0] = true;
        for (int num : nums) {
            for (int j = sum; j >= num; j--) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
        }
        return dp[sum];
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    return 0;
}