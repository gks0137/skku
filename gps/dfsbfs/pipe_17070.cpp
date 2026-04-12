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
    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }
    /* 0가로 1대각선 2세로*/
    pair<int, int> dxdy_by_dir[3] = {
        {0, 1},
        {1, 1},
        {1, 0}
    };
    vector<int> nextdir_by_dir[3] = {
        {0, 1},
        {0, 1, 2},
        {1, 2}
    };
    vector<pair<int, int>> checklist_by_dir[3] = {
        {{0, 1}},
        {{0, 1}, {1, 0}, {1, 1}},
        {{1, 0}}
    };
    //위치, 방향
    deque<pair<pair<int, int>, int>> q;
    q.push_back({{0, 1}, 0});
    int ans = 0;
    while (!q.empty()) {
        auto [pos, dir] = q.front();
        q.pop_front();
        auto [x, y] = pos;
        if (x == n - 1 && y == n - 1) {
            ans++;
            continue;
        }
        for (int nextdir : nextdir_by_dir[dir]) {
            bool can_move = true;
            for (auto checklist : checklist_by_dir[nextdir]) {
                int checkx = x + checklist.first;
                int checky = y + checklist.second;
                if (checkx >= n || checky >= n || board[checkx][checky] == 1) {
                    can_move = false;
                    break;
                }
            }
            if (can_move) {
                auto [dx, dy] = dxdy_by_dir[nextdir];
                q.push_back({{x + dx, y + dy}, nextdir});
            }
        }


    }
    cout << ans << "\n";

    

    return 0;
}
