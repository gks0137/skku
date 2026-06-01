#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> dp(nums.size(), INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 1; j <= nums[i] && i + j < nums.size(); j++) {
                dp[i + j] = min(dp[i + j], dp[i] + 1);
            }
        }
        return dp.back();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    vector<int> nums = {2,3,1,1,4};
    cout << sol.jump(nums) << endl;
    
    return 0;
}