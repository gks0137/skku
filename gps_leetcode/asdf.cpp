#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                res.push_back(nums[i]);
            }
        }
        for (int i = 0; i < res.size(); i++) {
            nums[i] = res[i];
        }
        return res.size();
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {3, 2, 2, 3};
    int val = 3;

    





    return 0;
}