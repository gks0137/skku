#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int uniqueCount = 0;
        set<int> seen;
        for (int num : nums) {
            if (seen.find(num) == seen.end()) {
                seen.insert(num);
                nums[uniqueCount] = num;
                uniqueCount++;
            }
        }
        return uniqueCount;
    }
};  


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {1, 1, 2};
    int result = sol.removeDuplicates(nums);
    cout << result << "\n";



    return 0;
}