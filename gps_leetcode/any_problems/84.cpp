#include <bits/stdc++.h>
using namespace std;



class minTree {
public:
    vector<int> heights;
    vector<int> minIdx;

    void build(int l, int r, int idx) {
        if (l == r) {
            minIdx[idx] = l;
            return;
        }
        int mid = (l + r) / 2;
        build(l, mid, 2 * idx + 1);
        build(mid + 1, r, 2 * idx + 2);
        if (heights[minIdx[2 * idx + 1]] < heights[minIdx[2 * idx + 2]]) {
            minIdx[idx] = minIdx[2 * idx + 1];
        } else {
            minIdx[idx] = minIdx[2 * idx + 2];
        }
    }

    pair<int, int> query(int l, int r, int ql, int qr, int idx) {
        if (ql > r || qr < l) {
            return {INT_MAX, -1};
        }
        if (ql <= l && r <= qr) {
            return {heights[minIdx[idx]], minIdx[idx]};
        }
        int mid = (l + r) / 2;
        auto leftResult = query(l, mid, ql, qr, 2 * idx + 1);
        auto rightResult = query(mid + 1, r, ql, qr, 2 * idx + 2);
        if (leftResult.first < rightResult.first) {
            return leftResult;
        } else {
            return rightResult;
        }
    }
};


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        minTree* root = new minTree();
        root->heights = heights;
        root->minIdx.resize(4 * n);
        root->build(0, n - 1, 0);

        int ans = 0;
        function<void(int, int)> f = [&](int l, int r) {
            if (l > r) return;
            auto [minHeight, minIdx] = root->query(0, n - 1, l, r, 0);
            ans = max(ans, minHeight * (r - l + 1));
            f(l, minIdx - 1);
            f(minIdx + 1, r);
        };
        f(0, n - 1);
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    
    vector<int> heights = {18, 8, 8};
    cout << sol.largestRectangleArea(heights) << endl;



    return 0;
}