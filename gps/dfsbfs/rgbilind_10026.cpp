#include <iostream>
#include <deque>
#include <vector>
#include <string>

int n;

std::vector<std::string> canvas;
std::vector<std::vector<bool>> visited_noraml;
std::vector<std::vector<bool>> visited_blind;

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

void push_valid(std::deque<std::pair<int, int>>& queue, std::pair<int, int> pos) {
    auto temp = get_adjacent(pos);
    for (const auto& where : temp) {
        if (canvas[where.first][where.second] == canvas[pos.first][pos.second]){
            if (!visited_noraml[where.first][where.second]){
                visited_noraml[where.first][where.second] = true;
                queue.push_back(where);
            }
        }
    }
}
void push_valid_blind(std::deque<std::pair<int, int>>& queue, std::pair<int, int> pos) {
    auto temp = get_adjacent(pos);
    for (const auto& where : temp) {
        if ((canvas[where.first][where.second] == 'B') == (canvas[pos.first][pos.second] == 'B')){
            if (!visited_blind[where.first][where.second]){
                visited_blind[where.first][where.second] = true;
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

    for (int i=0; i<n; i++) {
        std::string temp;
        std::cin >> temp;
        canvas.push_back(temp);
        visited_noraml.push_back({});
        visited_blind.push_back({});
        for (int ii=0; ii<n; ii++) {
            visited_noraml[i].push_back(false);
            visited_blind[i].push_back(false);
        }
    }

    std::deque<std::pair<int, int>> queue;
    int count=0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (visited_noraml[i][j]) {
                continue;
            }

            count ++;
                
            push_valid(queue, {i, j});

            while (!queue.empty())
            {
                auto v = queue.front();
                queue.pop_front();

                push_valid(queue, v);
            }
            
        }
    }
    std::cout << count << " ";


    queue.clear();
    count=0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (visited_blind[i][j]) {
                continue;
            }

            count ++;
                
            push_valid_blind(queue, {i, j});

            while (!queue.empty())
            {
                auto v = queue.front();
                queue.pop_front();

                push_valid_blind(queue, v);
            }
            
        }
    }
    std::cout << count;

    










    return 0;
}