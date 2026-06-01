#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        function<void(int)> backtrack = [&](int start) {
            if (start == nums.size()) {
                result.push_back(nums);
                return;
            }
            for (int i = start; i < nums.size(); ++i) {
                swap(nums[start], nums[i]);
                backtrack(start + 1);
                swap(nums[start], nums[i]);
            }
        };
        backtrack(0);
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    vector<int> nums = {1, 2, 3};
    vector<vector<int>> result = sol.permute(nums);
    
    return 0;
}