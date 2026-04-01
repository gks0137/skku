#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int t, m;
        std::cin >> t >> m;

        int pisono_period = 0;
        std::deque<int> fib;
        fib.push_back(0);
        fib.push_back(1);

        while (1) {
            fib.push_back((fib[0] + fib[1]) % m);
            fib.pop_front();
            ++pisono_period;
            if (fib[0] == 0 && fib[1] == 1) {
                break;
            }
        }

        std::cout << t << ' ' << pisono_period << "\n";
    }

    

    return 0;
}
