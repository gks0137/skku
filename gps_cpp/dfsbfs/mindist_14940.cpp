#include <iostream>
#include <vector>
#include <deque>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> dist;
int n, m;

vector<pair<int, int>> get_adjacent(int x, int y) {
    vector<pair<int, int>> adjacent;
    if (x > 0) adjacent.push_back({x - 1, y});
    if (x < n - 1) adjacent.push_back({x + 1, y});
    if (y > 0) adjacent.push_back({x, y - 1});
    if (y < m - 1) adjacent.push_back({x, y + 1});
    return adjacent;
}

void bfs(pair<int, int> start) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    deque<pair<int, int>> q;
    deque<int> q_dist;

    dist[start.first][start.second] = 0;

    visited[start.first][start.second] = true;
    q.push_back(start);
    q_dist.push_back(0);

    while (!q.empty()) {
        auto [x, y] = q.front();
        int current_dist = q_dist.front();
        q.pop_front();
        q_dist.pop_front();

        for (auto [nx, ny] : get_adjacent(x, y)) {
            if (!visited[nx][ny] && graph[nx][ny] == 1) {
                visited[nx][ny] = true;
                dist[nx][ny] = current_dist + 1;
                q.push_back({nx, ny});
                q_dist.push_back(current_dist + 1);
            }
        }
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    cin >> n >> m;
    graph.resize(n, vector<int>(m));
    dist.resize(n, vector<int>(m, -1));
    pair<int, int> target;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == 2) {
                target = {i, j}; // Store the target position
            }
        }
    }

    bfs(target);


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (graph[i][j] == 0) {
                cout << 0 << " ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << "\n";
    }


    return 0;
}