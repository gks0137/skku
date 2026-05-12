#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int* left = &height[0];
        int* right = &height[height.size() - 1];
        int max_area = 0;
        while (left < right) {
            int area = min(*left, *right) * (right - left);
            max_area = max(max_area, area);
            if (*left < *right) {
                left++;
            } else {
                right--;
            }
        }
        return max_area;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> height = {1,8,6,2,5,4,8,3,7};
    cout << sol.maxArea(height) << "\n";



    return 0;
}