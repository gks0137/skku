#include <iostream>
#include <vector>
#include <deque>

int n, m;
std::vector<std::string> grid;
std::vector<std::vector<std::vector<std::vector<bool>>>> visited;
std::deque<std::pair<int, int>> queue_R;
std::deque<std::pair<int, int>> queue_B;
std::deque<int> queue_move_count;

// Directions: 0 = up, 1 = down, 2 = left, 3 = right

void slide(std::pair<int, int>& R, std::pair<int, int>& B, int direction) {
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
    bool R_moving = true, B_moving = true;
    while (true) {
        if (R_moving) {
            int new_x = R.first + dx;
            int new_y = R.second + dy;
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m || grid[new_x][new_y] == '#') {
                R_moving = false; // Stop if we hit a wall or go out of bounds
            } else {
                R.first = new_x;
                R.second = new_y;
                if (grid[new_x][new_y] == 'O') {
                    R_moving = false; // Stop if we hit the hole
                } else if (!B_moving && R.first == B.first && R.second == B.second) {
                    R_moving = false; // Stop if R and B are in the same position
                    R.first -= dx; // Move R back to the last valid position
                    R.second -= dy;
                }
            }
        }
        if (B_moving) {
            int new_x = B.first + dx;
            int new_y = B.second + dy;
            if (new_x < 0 || new_x >= n || new_y < 0 || new_y >= m || grid[new_x][new_y] == '#') {
                B_moving = false; // Stop if we hit a wall or go out of bounds
                if (R.first == B.first && R.second == B.second) {
                    R_moving = false; // Stop R if B hits the wall and they are in the same position
                    R.first -= dx; // Move R back to the last valid position
                    R.second -= dy;
                }
            } else {
                B.first = new_x;
                B.second = new_y;
                if (grid[new_x][new_y] == 'O') {
                    B_moving = false; // Stop if we hit the hole
                } else if (R.first == B.first && R.second == B.second) {
                    B_moving = false; // Stop if R and B are in the same position
                    B.first -= dx; // Move B back to the last valid position
                    B.second -= dy;
                }
            }
        }
        if (!R_moving && !B_moving) {
            // Both R and B have stopped moving
            break;
        }
    }
}


void push_valid(std::pair<int, int> R, std::pair<int, int> B, int move_count) {
    
    for (int dir = 0; dir < 4; ++dir) {
        std::pair<int, int> new_R = R;
        std::pair<int, int> new_B = B;

        slide(new_R, new_B, dir);

        if (grid[new_B.first][new_B.second] == 'O') {
            continue; // Blue ball cannot go into the hole
        }
        if (grid[new_R.first][new_R.second] == 'O') {
            std::cout << move_count + 1 << "\n"; // Red ball goes into the hole
            exit(0);
        }

        if (!visited[new_R.first][new_R.second][new_B.first][new_B.second]) {
            visited[new_R.first][new_R.second][new_B.first][new_B.second] = true;
            queue_R.emplace_back(new_R);
            queue_B.emplace_back(new_B);
            queue_move_count.emplace_back(move_count + 1);
        }
    }
    

}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> n >> m;
    grid.resize(n);
    visited.resize(n, std::vector<std::vector<std::vector<bool>>>(m, std::vector<std::vector<bool>>(n, std::vector<bool>(m, false))));
    for (int i = 0; i < n; ++i) {
        std::cin >> grid[i];
    }

    std::pair<int, int> R, B;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'R') {
                R = {i, j};
                grid[i][j] = '.'; // Mark the initial position of R as empty
            } else if (grid[i][j] == 'B') {
                B = {i, j};
                grid[i][j] = '.'; // Mark the initial position of B as empty
            }
        }
    }

    queue_R.emplace_back(R);
    queue_B.emplace_back(B);
    queue_move_count.emplace_back(0);
    visited[R.first][R.second][B.first][B.second] = true;
    while (!queue_R.empty()) {
        std::pair<int, int> current_R = queue_R.front();
        std::pair<int, int> current_B = queue_B.front();
        int move_count = queue_move_count.front();
        queue_R.pop_front();
        queue_B.pop_front();
        queue_move_count.pop_front();

        if (move_count >= 10) {
            break; // Limit to 10 moves
        }

        // std::cout << "Current R: (" << current_R.first << ", " << current_R.second << "), Current B: (" << current_B.first << ", " << current_B.second << "), Move Count: " << move_count << "\n";

        push_valid(current_R, current_B, move_count);
    }


    std::cout << -1 << "\n"; // No solution found

    return 0;
}
