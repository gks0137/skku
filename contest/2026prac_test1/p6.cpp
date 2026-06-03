#include <iostream>
#include <deque>
#include <vector>

int n, m;

std::deque<std::pair<int, int>> queue;
std::vector<int> visited;
std::vector<std::vector<int>> adj;

void push_valid(std::pair<int, int> x){
    for (int i=0; i<n; i++) {
        int v = adj[x.first-1][i];
        if (v==0) continue;

        v = std::min(x.second, v);
        if (visited[i] < v) {
            queue.push_back({i+1, v});
            visited[i] = v;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n >> m;

    for (int i=0; i<n; i++) {
        std::vector<int> adjadj(n);
        adj.push_back(adjadj);
        visited.push_back(-1);
    }
    for (int i=0; i<m; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        adj[a-1][b-1] = std::max(adj[a-1][b-1], c);
        adj[b-1][a-1] = std::max(adj[b-1][a-1], c);
    }
    int q;
    std::cin >> q;
    for (int i=0; i<q; i++) {
        int start, end;
        std::cin >> start >> end;

        queue.clear();
        for (int temp=0; temp<n; temp++){
            visited[temp] = -1;
        }

        push_valid({start, 1000000000});
        while (!queue.empty())
        {
            std::pair<int, int> v = queue.front();
            queue.pop_front();

            push_valid(v);
        }
        
        std::cout << visited[end-1] << "\n";

    }



    return 0;
}