#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int pathlen = 0;
        int n = grid.size();
        int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        queue<pair<int, int>> q;
        q.push({0, 0});
        while (!q.empty()) {
            int size = q.size();
            pathlen++;
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] == 1) {
                    continue;
                }
                if (x == n - 1 && y == n - 1) {
                    return pathlen;
                }
                grid[x][y] = 1;
                for (int j = 0; j < 8; j++) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    q.push({nx, ny});
                }
            }
        }
        return -1;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol;


    return 0;
}