#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int countArrangement(int n) {
        int ans = 0;
        vector<int> nums(n + 1, 0);
        function<void(int)> track = [&](int k) {
            if (k > n) {
                ans++;
                return;
            }
            for (int i = 1; i <= n; i++) {
                if (!nums[i] && (i % k == 0 || k % i == 0)) {
                    nums[i] = k;
                    track(k + 1);
                    nums[i] = 0;
                }
            }
        };
        track(1);
        return ans;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol;

    int n = 6;
    cout << sol.countArrangement(n) << endl;

    return 0;
}