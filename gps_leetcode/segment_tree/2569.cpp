#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct lazy_segment_tree {
        vector<int> tree, lazy;
        int n;

        lazy_segment_tree(const vector<int>& nums) {
            n = nums.size();
            tree.resize(4 * n);
            lazy.resize(4 * n);
            build(nums, 1, 0, n - 1);
        }

        void build(const vector<int>& nums, int node, int start, int end) {
            if (start == end) {
                tree[node] = nums[start];
            } else {
                int mid = (start + end) / 2;
                build(nums, node * 2, start, mid);
                build(nums, node * 2 + 1, mid + 1, end);
                tree[node] = tree[node * 2] + tree[node * 2 + 1];
            }
        }

        void propagate(int node, int start, int end){
            if (lazy[node]) {
                if (start != end) {
                    int mid = (start + end) / 2;
                    tree[node * 2] = (mid - start + 1) - tree[node * 2];
                    tree[node * 2 + 1] = (end - mid) - tree[node * 2 + 1];
                    lazy[node * 2] ^= 1;
                    lazy[node * 2 + 1] ^= 1;
                }
                lazy[node] = 0;
            }
        }

        void update(int node, int start, int end, int l, int r) {
            if (r < start || l > end) {
                return;
            }
            if (l <= start && end <= r){
                tree[node] = (end - start + 1) - tree[node];
                lazy[node] ^= 1;
                return;
            }
            propagate(node, start, end);
            int mid = (start + end) / 2;
            update(node * 2, start, mid, l, r);
            update(node * 2 + 1, mid + 1, end, l, r);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }

    };

    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        lazy_segment_tree seg(nums1);
        long long sum_nums2 = accumulate(nums2.begin(), nums2.end(), 0LL);
        vector<long long> result;

        for (const auto& query : queries) {
            switch (query[0]) {
                case 1: {
                    seg.update(1, 0, seg.n - 1, query[1], query[2]);
                    // cout << seg.tree[1] << "\n";
                    break;
                }
                case 2: {
                    sum_nums2 += (long long)seg.tree[1] * query[1];
                    break;
                }
                case 3: {
                    result.push_back(sum_nums2);
                    break;
                }
            }
        }
        return result;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums1 = {0,0,0,0,1,0,0,0,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
    vector<int> nums2 = {30,46,43,34,39,16,14,41,22,11,32,2,44,12,22,36,44,49,50,10,33,7,42};
    vector<vector<int>> queries = {{1,15,21},{3,0,0},{3,0,0},{2,21,0},{2,13,0},{3,0,0}};
    vector<long long> result = sol.handleQuery(nums1, nums2, queries);
    for (long long res : result) {
        cout << res << "\n";
    }



    return 0;
}   