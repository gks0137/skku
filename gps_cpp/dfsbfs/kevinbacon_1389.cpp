#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int n;
vector<vector<int>> graph;
vector<int> kevin_bacon_numbers;

int bfs(int start, int end) {
    deque<int> q;
    deque<int> q_dist;
    vector<bool> visited(n, false);
    q.push_back(start);
    visited[start] = true;
    q_dist.push_back(0);


    while (!q.empty()) {
        int curr = q.front();
        q.pop_front();
        int curr_dist = q_dist.front();
        q_dist.pop_front();

        if (curr == end) {
            return curr_dist;
        }

        for (int next : graph[curr]) {
            if (!visited[next]) {
                visited[next] = true;
                q.push_back(next);
                q_dist.push_back(curr_dist + 1);
            }
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int m;
    std::cin >> n >> m;
    
    graph.resize(n, {});
    kevin_bacon_numbers.resize(n, 999999999);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += bfs(i, j);
            }
        }
        kevin_bacon_numbers[i] = sum;
    }

    int min_index = 0;
    for (int i = 1; i < n; i++) {
        if (kevin_bacon_numbers[i] < kevin_bacon_numbers[min_index]) {
            min_index = i;
        }
    }

    std::cout << min_index + 1 << "\n";

    return 0;
}
