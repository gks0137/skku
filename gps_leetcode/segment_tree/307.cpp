#include <bits/stdc++.h>
using namespace std;

class NumArray { // segement tree
public:
    vector<int> tree;
    int n;

    NumArray(vector<int>& nums) {
        n = nums.size();
        tree.resize(2 * n);
        for (int i = 0; i < n; i++) {
            tree[n + i] = nums[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
        }
    }
    
    void update(int index, int val) {
        index += n;
        tree[index] = val;
        while (index > 1) {
            index >>= 1;
            tree[index] = tree[index << 1] + tree[index << 1 | 1];
        }
    }
    
    int sumRange(int left, int right) {
        left += n;
        right += n;
        int sum = 0;
        while (left <= right) {
            if (left & 1) {
                sum += tree[left++];
            }
            if (!(right & 1)) {
                sum += tree[right--];
            }
            left >>= 1;
            right >>= 1;
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    vector<int> nums = {1, 3, 5};
    NumArray sol(nums);

    int left = 0, right = 2;
    cout << sol.sumRange(left, right) << "\n";

    int index = 1, val = 2;
    sol.update(index, val);

    int left2 = 0, right2 = 2;
    cout << sol.sumRange(left2, right2) << "\n";



    return 0;
}