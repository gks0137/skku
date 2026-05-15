#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result(nums.size(), 0);
        vector<int> sorted;
        
        for (int i = nums.size() - 1; i >= 0; --i) {
            auto it = lower_bound(sorted.begin(), sorted.end(), nums[i]);
            result[i] = it - sorted.begin();
            sorted.insert(it, nums[i]);
        }
        
        return result;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {5, 2, 6, 1};
    vector<int> result = sol.countSmaller(nums);
    for (int res : result) {
        cout << res << " ";
    }



    return 0;
}   
