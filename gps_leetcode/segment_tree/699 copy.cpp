#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<int> tree, lazy;
    int n;

    void propagate(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] = lazy[node];
            if (start != end) {
                lazy[2 * node] = lazy[node];
                lazy[2 * node + 1] = lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        propagate(node, start, end);
        if (start > r || end < l) return;

        if (l <= start && end <= r) {
            lazy[node] = val;
            propagate(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, l, r, val);
        updateRange(2 * node + 1, mid + 1, end, l, r, val);
        propagate(2 * node, start, mid);
        propagate(2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int queryRange(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;
        propagate(node, start, end);

        if (l <= start && end <= r) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int p1 = queryRange(2 * node, start, mid, l, r);
        int p2 = queryRange(2 * node + 1, mid + 1, end, l, r);
        return max(p1, p2);
    }

public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        // Coordinate compression: collect all x-coordinates
        set<int> coords_set;
        for (auto& pos : positions) {
            coords_set.insert(pos[0]);
            coords_set.insert(pos[0] + pos[1]);
        }
        vector<int> coords(coords_set.begin(), coords_set.end());
        n = coords.size();

        // Initialize segment tree
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        vector<int> result;
        int max_height = 0;

        for (auto& pos : positions) {
            int left = pos[0];
            int side = pos[1];
            int right = left + side;

            // Find indices in compressed coordinates
            int left_idx = lower_bound(coords.begin(), coords.end(), left) - coords.begin();
            int right_idx = lower_bound(coords.begin(), coords.end(), right) - coords.begin();

            // Query max height in range
            int h = queryRange(1, 0, n - 1, left_idx, right_idx - 1);

            // Update with new height
            int new_height = h + side;
            updateRange(1, 0, n - 1, left_idx, right_idx - 1, new_height);

            // Track global max
            max_height = max(max_height, new_height);
            result.push_back(max_height);
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<vector<int>> positions = {{9, 6}, {2, 2}, {2, 6}};
    vector<vector<int>> positions2 = {{100, 100}, {200, 100}};
    vector<int> result = sol.fallingSquares(positions);
    for (int height : result) {
        cout << height << " ";
    }



    return 0;
}   
