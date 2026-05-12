#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (size_t i = 0; i < nums.size() - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates
            int* left = &nums[i + 1], *right = &nums[nums.size() - 1];
            while (left < right) {
                int sum = nums[i] + *left + *right;
                if (sum == 0) {
                    result.push_back({nums[i], *left, *right});
                    while (left < right && *left == *(left + 1)) ++left; // Skip duplicates
                    while (left < right && *right == *(right - 1)) --right; // Skip duplicates
                    ++left;
                    --right;
                } else if (sum < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
        return result;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {-1,0,1,2,-1,-4};
    auto result = sol.threeSum(nums);
    for (const auto& triplet : result) {
        cout << "[";
        for (size_t i = 0; i < triplet.size(); ++i) {
            cout << triplet[i];
            if (i < triplet.size() - 1) cout << ",";
        }
        cout << "]\n";
    }

    return 0;
}