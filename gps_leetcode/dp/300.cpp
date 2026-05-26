#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> LIS;
        for (int num : nums) {
            if (LIS.empty() || LIS.back() < num) {
                LIS.push_back(num);
            } else {
                auto it = lower_bound(LIS.begin(), LIS.end(), num);
                *it = num;
            }
        }
        return LIS.size();
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << sol.lengthOfLIS(nums) << "\n";

    return 0;
}