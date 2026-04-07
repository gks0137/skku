#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n, m;
    std::cin >> n >> m;
    vector<int> board(101, 0);
    for (int i = 0; i < n + m; i++) {
        int x, y;
        std::cin >> x >> y;
        board[x] = y;
    }

    deque<int> q;
    q.push_back(1);
    vector<bool> visited(101, false);
    visited[1] = true;

    int ans = 0;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int cur = q.front();
            q.pop_front();
            if (cur == 100) {
                cout << ans;
                return 0;
            }
            for (int j = 1; j <= 6; j++) {
                int next = cur + j;
                if (next > 100) continue;
                if (board[next] != 0) next = board[next];
                if (!visited[next]) {
                    visited[next] = true;
                    q.push_back(next);
                }
            }
        }
        ans++;
    }
    cout << ans;
    

    return 0;
}
