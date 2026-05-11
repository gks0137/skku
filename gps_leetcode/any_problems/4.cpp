#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int l1_front = 0, l1_back = nums1.size()-1;
        int l2_front = 0, l2_back = nums2.size()-1;

        int median_low = -99999999, median_high = 99999999;

        while (l1_front <= l1_back || l2_front <= l2_back) {
            // low
            if (l1_front < nums1.size() && l2_front < nums2.size()) {
                if (nums1[l1_front] <= nums2[l2_front]) {
                    median_low = nums1[l1_front++];
                } else {
                    median_low = nums2[l2_front++];
                }
            } else if (l1_front < nums1.size()) {
                median_low = nums1[l1_front++];
            } else if (l2_front < nums2.size()) {
                median_low = nums2[l2_front++];
            } else {
                median_low = -99999999;
            }


            // high
            if (l1_back >= 0 && l2_back >= 0) {
                if (nums1[l1_back] >= nums2[l2_back]) {
                    median_high = nums1[l1_back--];
                } else {
                    median_high = nums2[l2_back--];
                }
            } else if (l1_back >= 0) {
                median_high = nums1[l1_back--];
            } else if (l2_back >= 0) {
                median_high = nums2[l2_back--];
            } else {
                median_high = 99999999;
            }
            // cout << "median_low: " << median_low << ", median_high: " << median_high << "\n";
        }

        return (median_low + median_high) / 2.0;


    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    vector<int> nums1 = {1};
    vector<int> nums2 = {};
    Solution sol;
    double median = sol.findMedianSortedArrays(nums1, nums2);
    cout << median << "\n";

    return 0;
}