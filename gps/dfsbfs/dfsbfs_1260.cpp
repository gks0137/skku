#include <iostream>
#include <deque>
#include <vector>
#include <set>

void dfs(std::vector<std::set<int>>& graph, std::vector<bool>& visited, int start){

    for (const auto& i : graph[start-1]) {
        if (!visited[i-1]) {
            std::cout << ' ' << i;
            visited[i-1] = true;
            dfs(graph, visited, i);
        }
    }
}

void bfs(std::vector<std::set<int>>& graph, std::vector<bool>& visited, int start) {
    std::deque<int> queue;
    for (const int i : graph[start-1]){
        queue.push_back(i);
        visited[i-1] = true;
    }
    while (!queue.empty())
    {
        int v = queue.front();
        queue.pop_front();
        std::cout << ' ' << v;
        for (const int i : graph[v-1]) {
            if (!visited[i-1]) {
                queue.push_back(i);
                visited[i-1] = true;
            }
        }
    }
}




int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m, v;
    std::cin >> n >> m >> v;

    std::vector<std::set<int>> graph(n);

    for (int i=0; i<m; i++) {
        int a, b;
        std::cin >> a >> b;

        graph[a-1].insert(b);
        graph[b-1].insert(a);
    }

    //dfs

    std::vector<bool> visited(n);
    for(int i=0; i<n; i++) visited[i] = false;
    std::cout << v;
    visited[v-1] = true;
    dfs(graph, visited, v);
    

    //bfs

    for(int i=0; i<n; i++) visited[i] = false;
    std::cout << "\n" << v;
    visited[v-1] = true;
    bfs(graph, visited, v);
    

    return 0;
}