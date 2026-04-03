#include <iostream>
#include <deque>
#include <vector>

int n, m;

std::vector<std::vector<int>> lattice;

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
        
        if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
            adjacents.push_back({nx, ny});
        }
    }

    return adjacents;
}

void push_valid(std::pair<int, int> pos) {
    auto temp = get_adjacent(pos);
    for (const auto& where : temp) {
        if (lattice[where.first][where.second] == 1){
            if (!visited[where.first][where.second]){
                visited[where.first][where.second] = true;
                queue.push_back(where);
            }
        }
    }
}


int main() {    
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int t;
    std::cin >> t;
    for (int tc=0; tc<t; tc++) {

        int N, M, k;
        std::cin >> N >> M >> k;

        n = N;
        m = M;

        lattice = std::vector<std::vector<int>>(n, std::vector<int>(m, 0));
        visited = std::vector<std::vector<bool>>(n, std::vector<bool>(m, false));

        for (int i=0; i<k; i++) {
            int x, y;
            std::cin >> x >> y;
            lattice[x][y] = 1;
        }

        int count=0;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (lattice[i][j] == 0 || visited[i][j]) {
                    continue;
                }

                count ++;
                    
                push_valid({i, j});
                visited[i][j] = true;

                while (!queue.empty())
                {
                    auto v = queue.front();
                    queue.pop_front();
                    
                    //std::cout << "v: " << v.first << ", " << v.second << "\n";

                    push_valid(v);
                }
                
            }
        }

        

        std::cout << count << "\n";


    }





    return 0;
}