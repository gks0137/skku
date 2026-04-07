#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> graph;

int get_tetromino_1(pair<int, int> start, vector<pair<int, int>> tetromino) {
    int sum = 0;
    for (auto p : tetromino) {
        int x = start.first + p.first;
        int y = start.second + p.second;
        if (x < 0 || x >= n || y < 0 || y >= m) {
            return 0;
        }
        sum += graph[x][y];
    }
    // if (sum == 21) {
    //     cout << "start: (" << start.first << ", " << start.second << ")\n";
    //     cout << "tetromino: " << "[";
    //     for (auto p : tetromino) {
    //         cout << "(" << p.first << ", " << p.second << ") ";
    //     }
    //     cout << "]\n";
    // }
    return sum;
}

int get_max_tetromino(pair<int, int> start) {
    int max_sum = 0;
    vector<vector<pair<int, int>>> tetrominoes = {
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}}, // I
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}}, // I
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, // O

        {{0, 0}, {1, 0}, {2, 0}, {2, 1}}, // L
        {{0, 0}, {1, 0}, {2, 0}, {0, 1}}, // L
        {{0, 1}, {1, 1}, {2, 1}, {0, 0}}, // L
        {{0, 1}, {1, 1}, {2, 1}, {2, 0}}, // L

        {{0, 0}, {0, 1}, {0, 2}, {1, 0}}, // L
        {{0, 0}, {0, 1}, {0, 2}, {1, 2}}, // L
        {{1, 0}, {1, 1}, {1, 2}, {0, 0}}, // L
        {{1, 0}, {1, 1}, {1, 2}, {0, 2}}, // L

        {{0, 0}, {1, 0}, {1, 1}, {2, 1}}, // S
        {{0, 1}, {1, 1}, {1, 0}, {2, 0}}, // S
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}}, // S
        {{1, 0}, {1, 1}, {0, 1}, {0, 2}}, // S

        {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, // T
        {{0, 0}, {1, 0}, {2, 0}, {1, 1}}, // T
        {{0, 1}, {1, 0}, {1, 1}, {2, 1}}, // T
        {{1, 0}, {0, 1}, {1, 1}, {1, 2}} // T
    };
    for (const auto& tetromino : tetrominoes) {
        max_sum = std::max(max_sum, get_tetromino_1(start, tetromino));
    }
    return max_sum;

}



int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    std::cin >> n >> m;
    
    graph.resize(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> graph[i][j];
        }
    }
    
    int max_sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            max_sum = std::max(max_sum, get_max_tetromino({i, j}));
        }
    }
    std::cout << max_sum;

    

    return 0;
}
