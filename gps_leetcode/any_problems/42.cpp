#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int trap(vector<int>& height) {
        vector<int> Max(height.size(), INT_MAX);
        int pMax = 0;
        for (int i = 0; i < height.size(); ++i) {
            pMax = max(pMax, height[i]);
            Max[i] = pMax;
        }
        pMax = 0;
        for (int i = height.size() - 1; i >= 0; --i) {
            pMax = max(pMax, height[i]);
            Max[i] = min(Max[i], pMax);
        }
        int res = 0;
        for (int i = 0; i < height.size(); ++i) {
            res += Max[i] - height[i];
        }
        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    vector<int> nums = {0,1,0,2,1,0,1,3,2,1,2,1};
    int result = sol.trap(nums);
    cout << result << endl;



    return 0;
}