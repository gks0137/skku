#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int *start = &nums[0], *end = &nums[nums.size() - 1], *p = end;
        while (p > start && *p <= *(p - 1)) {
            p--;
        }
        if (p == start) {
            reverse(start, end + 1);
        } else if (p == end) {
            swap(*p, *(p - 1));
        } else {
            sort(p, end + 1);
            auto it = upper_bound(p, end + 1, *(p - 1));
            swap(*(p - 1), *it);
        }
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> num_vec = {1, 4, 5, 3, 2};
    sol.nextPermutation(num_vec);

    cout << "Next permutation: ";
    for (int num : num_vec) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}