#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = *max_element(piles.begin(), piles.end());
        int ans = right;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long hours_needed = 0;

            for (int pile : piles) {
                hours_needed += (pile + mid - 1) / mid;
            }

            if (hours_needed <= h) {
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