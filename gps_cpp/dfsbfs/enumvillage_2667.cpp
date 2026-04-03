#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>

int n;

std::vector<std::vector<int>> lattice;
std::vector<std::vector<int>> village_map;

std::vector<std::vector<bool>> visited;
std::deque<std::pair<int, int>> queue;

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
        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            adjacents.push_back({nx, ny});
        }
    }

    return adjacents;
}

void push_valid(std::pair<int, int> pos, int village_num) {
    auto temp = get_adjacent(pos);
    for (const auto& where : temp) {
        if (lattice[where.first][where.second] == 1){
            if (!visited[where.first][where.second]){
                visited[where.first][where.second] = true;
                village_map[where.first][where.second] = village_num;
                queue.push_back(where);
            }
        }
    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n;

    lattice.resize(n, std::vector<int>(n, 0));
    village_map.resize(n, std::vector<int>(n, 0));
    visited.resize(n, std::vector<bool>(n, false));

    for (int i=0; i<n; i++) {
        std::string temp;
        std::cin >> temp;
        for (int j=0; j<n; j++) {
            lattice[i][j] = temp[j] - '0';
        }
    }

    int count=0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (lattice[i][j] == 0 || visited[i][j]) {
                continue;
            }

            count ++;
                
            push_valid({i, j}, count);
            village_map[i][j] = count;
            visited[i][j] = true;

            while (!queue.empty())
            {
                auto v = queue.front();
                queue.pop_front();

                push_valid(v, count);
            }
            
        }
    }

    // for (int i=0; i<n; i++) {
    //     for (int j=0; j<n; j++) {
    //         std::cout << village_map[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }
    
    std::vector<int> result(count, 0);

    if (count == 0) {
        std::cout << 0 << "\n";
        return 0;
    }



    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (visited[i][j]) {
                result[village_map[i][j] - 1] ++;
            }
        }
    }

    std::sort(result.begin(), result.end());

    std::cout << count << "\n";
    for (const auto& r : result) {
        std::cout << r << "\n";
    }






    return 0;
}