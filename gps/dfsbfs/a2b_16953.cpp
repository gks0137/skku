#include <iostream>
#include <deque>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    long long a, b;
    std::cin >> a >> b;


    deque<long long> q;
    q.push_back(a);
    int cnt = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            long long cur = q.front();
            q.pop_front();

            if (cur == b) {
                cout << cnt + 1;
                return 0;
            }

            if (cur * 2 <= b) {
                q.push_back(cur * 2);
            }
            if (cur * 10 + 1 <= b) {
                q.push_back(cur * 10 + 1);
            }
        }
        cnt++;
    }
    cout << -1;

    return 0;
}
