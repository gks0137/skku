#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        vector<vector<int>> ans;
        vector<vector<bool>> pacific(n, vector<bool>(m, false));
        vector<vector<bool>> atlantic(n, vector<bool>(m, false));

        function<void(int, int, vector<vector<bool>>&)> dfs = [&](int i, int j, vector<vector<bool>>& ocean) {
            if (ocean[i][j]) return;
            ocean[i][j] = true;
            vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto& dir : directions) {
                int x = i + dir.first, y = j + dir.second;
                if (x >= 0 && x < n && y >= 0 && y < m && heights[x][y] >= heights[i][j]) {
                    dfs(x, y, ocean);
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            dfs(i, 0, pacific);
            dfs(i, m - 1, atlantic);
        }

        for (int j = 0; j < m; ++j) {
            dfs(0, j, pacific);
            dfs(n - 1, j, atlantic);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    ans.push_back({i, j});
                }
            }
        }

        return ans;

    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;



    return 0;
}