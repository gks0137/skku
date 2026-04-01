#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int q, m;
    std::cin >> q >> m;

    std::deque<int> fib = {0, 1};
    std::deque<int> music = {0, 1};

    while (1) {
        int next_fib = (fib[fib.size() - 2] + fib[fib.size() - 1]) % m;
        fib.push_back(next_fib);

        std::deque<int> next_fib_10;
        if (next_fib == 0) {
            music.push_back(0);
            continue;
        }
        while (next_fib)
        {
            next_fib_10.push_front(next_fib % 10);
            next_fib /= 10;
        }
        for (int i = 0; i < next_fib_10.size(); ++i) {
            music.push_back(next_fib_10[i]);
        }

        if (fib[fib.size() - 2] == 0 && fib[fib.size() - 1] == 1) {
            break;
        }
    }

    for (int i = 0; i < q; ++i)
    {
        long long int n;
        std::cin >> n;
        
        int remainder = (int)(n % (music.size() - 2));

        std::cout << music[remainder] << "\n";

    }
    return 0;
}
