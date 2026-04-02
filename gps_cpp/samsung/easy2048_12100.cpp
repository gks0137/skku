#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

int n;
std::unordered_map<std::string, bool> visited;
std::deque<std::vector<std::vector<int>>> queue_grid;
std::deque<int> queue_move_count;

// Directions: 0 = up, 1 = down, 2 = left, 3 = right

std::string hash_grid(const std::vector<std::vector<int>>& grid) {
    std::string hash_value = "";
    for (const auto& row : grid) {
        for (int cell : row) {
            hash_value += std::to_string(cell) + ",";
        }
    }
    return hash_value;
}

void slide(std::vector<std::vector<int>>& grid, int direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 0: // up
            dx = -1;
            break;
        case 1: // down
            dx = 1;
            break;
        case 2: // left
            dy = -1;
            break;
        case 3: // right
            dy = 1;
            break;
    }
    int start, end, step;
    if (dx == 1 || dy == 1) {
        start = n - 1;
        end = -1;
        step = -1;
    } else {
        start = 0;
        end = n;
        step = 1;
    }
    std::unordered_map<std::string, bool> already_merged;
    
    for (int i = start; i != end; i += step) {
        for (int j = start; j != end; j += step) {
            int x = i, y = j;
            if (grid[x][y] == 0) {
                continue;
            }
            int next_x = x + dx, next_y = y + dy;
            while (next_x >= 0 && next_x < n && next_y >= 0 && next_y < n) {
                if (grid[next_x][next_y] == 0) {
                    grid[next_x][next_y] = grid[x][y];
                    grid[x][y] = 0;
                    x = next_x;
                    y = next_y;
                    next_x += dx;
                    next_y += dy;
                } else if (grid[next_x][next_y] == grid[x][y] && !already_merged[hash_grid({{next_x, next_y}})]) {
                    grid[next_x][next_y] *= 2;
                    grid[x][y] = 0;
                    already_merged[hash_grid({{next_x, next_y}})] = true;
                    break;
                } else {
                    break;
                }
                
            }

        }
    }
}

void push_valid(std::vector<std::vector<int>> grid, int move_count) {
    
    for (int dir = 0; dir < 4; ++dir) {
        std::vector<std::vector<int>> new_grid = grid;
        slide(new_grid, dir);
        if (visited[hash_grid(new_grid)]) {
            continue;
        }
        visited[hash_grid(new_grid)] = true;
        queue_grid.push_back(new_grid);
        queue_move_count.push_back(move_count + 1);
    }
    

}

int get_max_tile(const std::vector<std::vector<int>>& grid) {
    int max_tile = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            max_tile = std::max(max_tile, cell);
        }
    }
    return max_tile;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n;
    std::vector<std::vector<int>> grid_original(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> grid_original[i][j];
        }
    }

    int max_tile = 0;
    
    visited[hash_grid(grid_original)] = true;
    queue_grid.push_back(grid_original);
    queue_move_count.push_back(0);

    while (!queue_grid.empty()) {
        std::vector<std::vector<int>> current_grid = queue_grid.front();
        int current_move_count = queue_move_count.front();
        queue_grid.pop_front();
        queue_move_count.pop_front();

        // for (const auto& row : current_grid) {
        //     for (int cell : row) {
        //         std::cout << cell << " ";
        //     }
        //     std::cout << "\n";
        // } std::cout << "Move count: " << current_move_count << "\n\n";

        int current_max_tile = get_max_tile(current_grid);
        max_tile = std::max(max_tile, current_max_tile);

        if (current_move_count >= 5) {
            continue;
        }

        push_valid(current_grid, current_move_count);
    }
    
    std::cout << max_tile << "\n";

    

    return 0;
}
