#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        deque<pair<int, int>> queue;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    count++;
                    queue.push_back({i, j});
                    visited[i][j] = true;
                    while (!queue.empty()) {
                        auto [x, y] = queue.front();
                        queue.pop_front();
                        for (int k = 0; k < 4; k++) {
                            int nx = x + dx[k];
                            int ny = y + dy[k];
                            if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == '1' && !visited[nx][ny]) {
                                queue.push_back({nx, ny});
                                visited[nx][ny] = true;
                            }
                        }
                    }
                }
            }
        }
        return count;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    vector<vector<char>> grid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    cout << sol.numIslands(grid) << "\n";

    return 0;
}