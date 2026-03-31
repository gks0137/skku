#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <tuple>


int n, m;

std::vector<std::string> map;
std::vector<std::vector<int>> visited;

std::vector<std::pair<int, int>> get_adjacent(std::pair<int, int> pos) {
    std::vector<std::pair<int, int>> adjacents;
    
    int x = pos.first;
    int y = pos.second;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // 좌표가 n * m * h 범위 내에 있는지 확인 (0-based index 기준)
        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
            adjacents.push_back({nx, ny});
        }
    }

    return adjacents;
}

void push_valid(std::deque<std::tuple<int, int, bool, int>>& queue, std::tuple<int, int, bool, int> temp) {
    auto adj = get_adjacent({std::get<0>(temp), std::get<1>(temp)});
    bool breaking = std::get<2>(temp);
    int c = std::get<3>(temp);
    for (const auto& where : adj) {
        int x = std::get<0>(where);
        int y = std::get<1>(where);
        bool breaking_temp = breaking;

        if (map[x][y]=='1') {
            if (breaking) {
                breaking_temp = false;
            } else {
                continue;
            }
        }
        if (visited[x][y] == 0) {
            visited[x][y] = breaking_temp ? 1 : 2;
            queue.push_back({x, y, breaking_temp, c+1});
        } else if (visited[x][y] == 2 && breaking_temp) {
                visited[x][y] = 1;
                queue.push_back({x, y, breaking_temp, c+1});
        }
        
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n >> m;

    for (int i=0; i<n; i++) {
        std::string temp;
        std::cin >> temp;
        map.push_back(temp);
        visited.push_back({});
        for (int ii=0; ii<m; ii++) {
            visited[i].push_back(0);
        }
    }

    std::deque<std::tuple<int, int, bool, int>> queue;



    queue.push_back({0, 0, true, 1});
    visited[0][0] = 1;

    while (!queue.empty())
    {
        auto v = queue.front();
        queue.pop_front();
        
        //std::cout << std::get<0>(v) << std::get<1>(v) << "\n";

        if (std::get<0>(v)==n-1 && std::get<1>(v)==m-1) {
            std::cout << std::get<3>(v);
            return 0;
        }

        push_valid(queue, v);
    }

    
    std::cout << -1;


    










    return 0;
}