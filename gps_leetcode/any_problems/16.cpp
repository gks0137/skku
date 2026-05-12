#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int closest = nums[0] + nums[1] + nums[2];
        for (size_t i = 0; i < nums.size() - 2; ++i) {
            int* left = &nums[i + 1], *right = &nums[nums.size() - 1];
            while (left < right) {
                int sum = nums[i] + *left + *right;
                if (abs(sum - target) < abs(closest - target)) {
                    closest = sum;
                }
                if (sum == target) {
                    return sum;
                } else if (sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }
        }
        return closest;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {-1, 2, 1, -4};
    int target = 1;
    int result = sol.threeSumClosest(nums, target);
    cout << result << "\n";

    return 0;
}
