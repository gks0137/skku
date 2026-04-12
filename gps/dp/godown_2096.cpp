#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n;
    cin >> n;
    vector<int> game_board[3] = {vector<int>(n), vector<int>(n), vector<int>(n)};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> game_board[j][i];
        }
    }
    deque<int> dp_max[3] = {{0}, {0}, {0}};
    deque<int> dp_min[3] = {{0}, {0}, {0}};
    vector<vector<int>> filter = {{0, 1}, {0, 1, 2}, {1, 2}};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            int max_value = 0;
            int min_value = 1000000000;
            for (int k : filter[j]) {
                max_value = max(max_value, dp_max[k][0]);
                min_value = min(min_value, dp_min[k][0]);
            }
            dp_max[j].push_back(max_value + game_board[j][i]);
            dp_min[j].push_back(min_value + game_board[j][i]);
        }
        for (int j = 0; j < 3; j++) {
            dp_max[j].pop_front();
            dp_min[j].pop_front();
        }

        
    }
    int max_value = 0;
    int min_value = 1000000000;
    for (int i = 0; i < 3; i++) {
        max_value = max(max_value, dp_max[i][0]);
        min_value = min(min_value, dp_min[i][0]);
    }
    cout << max_value << " " << min_value << "\n";

    

    

    return 0;
}
