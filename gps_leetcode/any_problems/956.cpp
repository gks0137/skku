#include <bits/stdc++.h>
using namespace std;




class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        unordered_map<int, int> dp;
        dp[0] = 0;

        for (int rod : rods) {
            unordered_map<int, int> new_dp(dp);
            for (const auto& [diff, sum] : dp) {
                // Add rod to the first billboard
                new_dp[diff + rod] = max(new_dp[diff + rod], sum + rod);
                // Add rod to the second billboard
                if (diff >= rod) {
                    new_dp[diff - rod] = max(new_dp[diff - rod], sum);
                } else {
                    new_dp[rod - diff] = max(new_dp[rod - diff], sum - diff + rod);
                }
            }
            dp.swap(new_dp);
        }

        return dp[0];
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    vector<int> rods = {1,2,4,8,16,32,64,128,256,512,50,50,50,150,150,150,100,100,100,123};
    cout << sol.tallestBillboard(rods) << endl;

    vector<int> rods2 = {3, 4, 3, 3, 2};
    cout << sol.tallestBillboard(rods2) << endl;

    return 0;
}