#include <iostream>
#include <deque>
#include <vector>

int n, m;

std::vector<std::vector<int>> graph;

std::vector<bool> visited;
std::deque<int> queue;



int main() {    
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m;
    std::cin >> n >> m;
    graph.resize(n, {});
    visited.resize(n, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int component_count = 0;
    for (int i = 0; i < n; i++) {
        
        if (!visited[i]) {
            visited[i] = true;
            queue.push_back(i);
            while (!queue.empty()) {
                int current = queue.front();
                queue.pop_front();
                
                for (int neighbor : graph[current]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        queue.push_back(neighbor);
                    }
                }
            }
            component_count++;
        }
    }

    std::cout << component_count << "\n";


    return 0;
}