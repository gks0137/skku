#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int* left = &nums[0], * right = &nums[0] + nums.size() - 1, * i = &nums[0];
        while (i <= right) {
            if (*i == 0) {
                swap(*i, *left);
                left++;
                i++;
            } else if (*i == 2) {
                swap(*i, *right);
                right--;
            } else {
                i++;
            }
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol;

    vector<int> nums1 = {2,0, 2,1,1,0};
    sol.sortColors(nums1);
    for (int n : nums1) {
        cout << n << " ";
    }

    return 0;
}