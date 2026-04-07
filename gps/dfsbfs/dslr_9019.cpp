#include <iostream>
#include <deque>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int t;
    std::cin >> t;

    while (t--) {
        int a, b;
        std::cin >> a >> b;

        deque<pair<int, string>> q;
        q.push_back({a, ""});
        bool visited[10000] = {false};
        visited[a] = true;

        while (!q.empty()) {
            int num = q.front().first;
            string cmd = q.front().second;
            q.pop_front();

            if (num == b) {
                std::cout << cmd << "\n";
                break;
            }

            // D
            int d_num = (num * 2) % 10000;
            if (!visited[d_num]) {
                visited[d_num] = true;
                q.push_back({d_num, cmd + "D"});
            }

            // S
            int s_num = (num == 0) ? 9999 : num - 1;
            if (!visited[s_num]) {
                visited[s_num] = true;
                q.push_back({s_num, cmd + "S"});
            }

            // L
            int l_num = (num % 1000) * 10 + num / 1000;
            if (!visited[l_num]) {
                visited[l_num] = true;
                q.push_back({l_num, cmd + "L"});
            }

            // R
            int r_num = (num / 10) + (num % 10) * 1000;
            if (!visited[r_num]) {
                visited[r_num] = true;
                q.push_back({r_num, cmd + "R"});
            }
        }
    }

    

    return 0;
}
