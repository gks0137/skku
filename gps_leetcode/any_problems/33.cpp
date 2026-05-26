#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int size = nums.size(), answer = -1, idx0 = nums[0];
        int left = 0, right = 2 * size - 1;
        while (left <= right) {
            int mid = (left + right) / 2, mid_val = nums[mid % size];
            if (mid_val == target) {
                answer = mid % size;
                break;
            }
            if (mid < size) {
                if (mid_val < idx0 && target < mid_val) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (mid_val < target && mid_val >= idx0) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return answer;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {4,5,6,7,0,1,2};
    int target = 0;
    cout << sol.search(nums, target) << '\n';

    return 0;
}