#include <iostream>
#include <vector>
#include <deque>
using namespace std;



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    
    int n, m, friend_count = 0;
    std::cin >> n >> m;
    vector<string> world(n);
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    deque<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        std::cin >> world[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (world[i][j] == 'I'){
                q.push_back({i, j});
                visited[i][j] = true;
                break;
            }
        }
    }
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();

        if (world[x][y] == 'P') {
            friend_count++;
        }

        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (!visited[nx][ny] && world[nx][ny] != 'X') {
                        visited[nx][ny] = true;
                        q.push_back({nx, ny});
                    }
                }
            
        }
    }

    if (friend_count == 0) {
        std::cout << "TT\n";
    } else {
        std::cout << friend_count << "\n";
    }

    

    return 0;
}
