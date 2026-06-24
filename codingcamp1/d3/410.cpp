#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int left = *max_element(nums.begin(), nums.end());
        int right = accumulate(nums.begin(), nums.end(), 0);
        int ans = right;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int current_sum = 0;
            int required_subarrays = 1;

            for (int num : nums) {
                if (current_sum + num > mid) {
                    required_subarrays++;
                    current_sum = num;
                } else {
                    current_sum += num;
                }
            }

            if (required_subarrays <= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;

    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    return 0;
}