#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    long long int n;
    std::cin >> n;

    int modulo = 1000000;
    int pisono_period = 1500000;
    int remainder = (int)(n % pisono_period);
    std::deque<int> fib;
    fib.push_back(0);
    fib.push_back(1);

    if (remainder == 0) {
        std::cout << 0 << "\n";
        return 0;
    } else if (remainder == 1) {
        std::cout << 1 << "\n";
        return 0;
    }

    for (int i = 2; i <= remainder; ++i) {
        fib.push_back((fib[0] + fib[1]) % modulo);
        fib.pop_front();
    }

    std::cout << fib[1] << "\n";

    

    

    return 0;
}
