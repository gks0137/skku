#include <iostream>
#include <deque>
#include <vector>
using namespace std;


int m, n;
vector<vector<int>> box;
vector<vector<bool>> visited;
deque<int> queue_x;
deque<int> queue_y;
deque<int> queue_c;



vector<pair<int, int>> get_adjacent(pair<int, int> pos) {
    vector<pair<int, int>> adjacents;

    if (pos.first > 0) adjacents.push_back({pos.first - 1, pos.second});
    if (pos.first < n - 1) adjacents.push_back({pos.first + 1, pos.second});
    if (pos.second > 0) adjacents.push_back({pos.first, pos.second - 1});
    if (pos.second < m - 1) adjacents.push_back({pos.first, pos.second + 1});

    return adjacents;
}

void push_valid(pair<int, int> pos, int c) {
    for (auto adjacent : get_adjacent(pos)) {
        if (!visited[adjacent.first][adjacent.second] && box[adjacent.first][adjacent.second] == 0) {
            visited[adjacent.first][adjacent.second] = true;
            queue_x.push_back(adjacent.first);
            queue_y.push_back(adjacent.second);
            queue_c.push_back(c + 1);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> m >> n;
    box.resize(n, vector<int>(m));
    visited.resize(n, vector<bool>(m, false));


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> box[i][j];
            if (box[i][j] == 1) {
                queue_x.push_back(i);
                queue_y.push_back(j);
                queue_c.push_back(0);
                visited[i][j] = true;
            }
        }
    }

    int max_days = 0;

    while (!queue_x.empty()) {
        int x = queue_x.front();
        int y = queue_y.front();
        int c = queue_c.front();
        queue_x.pop_front();
        queue_y.pop_front();
        queue_c.pop_front();

        max_days = std::max(max_days, c);

        push_valid({x, y}, c);
    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (box[i][j] == 0 && !visited[i][j]) {
                std::cout << -1;
                return 0;
            }
        }
    }
    std::cout << max_days;
    



    return 0;
}

