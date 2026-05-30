#include <bits/stdc++.h>
using namespace std;

int dfs(vector<vector<bool>>& grid, int s, int e, int n) {
    vector<bool> visited(n, false);
    deque<pair<int, int>> q;
    q.push_back({s, 0});
    visited[s] = true;

    while(!q.empty()) {
        auto [x, c] = q.front();
        q.pop_front();

        if (x == e) {
            return c;
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i] && grid[x][i]) {
                visited[i] = true;
                q.push_back({i, c+1});
            }
        }
    }

    return 100000001;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    int v1, v2, v3, m1, m2;
    cin >> v1 >> v2 >> v3 >> m1 >> m2;
    v1--;v2--;v3--;
    vector<vector<bool>>grid(n, vector<bool>(n, false));
    
    while(m--) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        grid[x][y] = true;
        grid[y][x] = true;
    }

    long long ans = m1*m1;
    ans *= dfs(grid, v1, v2, n);
    long long asdf = m2*m2;
    ans += asdf *= dfs(grid, v2, v3, n);

    cout << ans;

    return 0;
}