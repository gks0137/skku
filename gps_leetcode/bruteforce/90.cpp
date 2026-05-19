

#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> subsets;

    void backtrack(const vector<int>& nums, vector<int>& current, int index) {
        subsets.push_back(current);
        for (int i = index; i < nums.size(); ++i) {
            if (i > index && nums[i] == nums[i - 1]) continue; // Skip duplicates
            current.push_back(nums[i]);
            backtrack(nums, current, i + 1);
            current.pop_back();
        }
    }


    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        subsets.clear();
        vector<int> current;
        backtrack(nums, current, 0);
        return subsets;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {1, 2, 2};
    vector<vector<int>> res = sol.subsetsWithDup(nums);
    for (const auto& subset : res) {
        cout << "[";
        for (size_t i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }


    return 0;
}