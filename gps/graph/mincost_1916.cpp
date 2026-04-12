#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n, m;
    cin >> n >> m;
    // destination, cost
    vector<pair<int, int>> graph[n + 1];
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }
    int start, end;
    cin >> start >> end;

    // cost, destination
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n + 1, 1e9);
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [cost, node] = pq.top();
        pq.pop();
        if (dist[node] < cost) continue;
        for (auto [next, nextCost] : graph[node]) {
            if (dist[next] > cost + nextCost) {
                dist[next] = cost + nextCost;
                pq.push({dist[next], next});
            }
        }
    }

    cout << dist[end] << "\n";

    return 0;
}
