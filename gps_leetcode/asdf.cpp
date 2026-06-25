#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int cur_state, ans = -1;
        for (int i = 0; i < n; i++) {
            cur_state = 0;
            for (int j = i; j < n; j++) {
                cur_state += nums[j] == target ? 1 : -1;
                if (cur_state > 0) {
                    ans++;
                }
            }
        }
        return ans;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    





    return 0;
}