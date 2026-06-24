#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);
        int ans = right;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int current_sum = 0;
            int required_days = 1;

            for (int weight : weights) {
                if (current_sum + weight > mid) {
                    required_days++;
                    current_sum = weight;
                } else {
                    current_sum += weight;
                }
            }

            if (required_days <= days) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        ans *= 2;
        ans %= 1000000007;
        return ans;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    return 0;
}