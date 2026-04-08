#include <iostream>
#include <queue>
#include <vector>

#define INF 1e9

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n, e, start;
    std::cin >> n >> e >> start;
    start--;
    // graph[node] = vector of (cost, nextNode)
    std::vector<std::pair<int, int>> graph[n];
    for (int i = 0; i < e; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        graph[a - 1].push_back(std::make_pair(b - 1, w));
    }

    //dijkstra
    int dist[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;
    // (cost, node)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, start));
    while(!pq.empty()) {
        int cost = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if (dist[node] < cost) {
            continue;
        }
        for (const auto& next : graph[node]) {
            int nextCost = cost + next.second;
            int nextNode = next.first;
            if (dist[nextNode] > nextCost) {
                dist[nextNode] = nextCost;
                pq.push(std::make_pair(nextCost, nextNode));
            }
        }
    }
    
    

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            std::cout << "INF\n";
        } else {
            std::cout << dist[i] << "\n";
        }
    }
    


    return 0;
}
