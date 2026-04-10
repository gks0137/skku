#include <iostream>
#include <unordered_map>

std::unordered_map<long long, long long> fibo;


long long fibonacci(long long n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }
    if (n & 1) {
        if (fibo.find((n-1) / 2) == fibo.end()) {
            fibo[(n-1) / 2] = fibonacci((n-1) / 2);
        }
        if (fibo.find((n+1) / 2) == fibo.end()) {
            fibo[(n+1) / 2] = fibonacci((n+1) / 2);
        }
        return (fibo[(n+1) / 2] * fibo[(n+1) / 2] + fibo[(n-1) / 2] * fibo[(n-1) / 2]) % 1000000007;
    } else {
        if (fibo.find(n / 2) == fibo.end()) {
            fibo[n / 2] = fibonacci(n / 2);
        }
        if (fibo.find(n / 2 - 1) == fibo.end()) {
            fibo[n / 2 - 1] = fibonacci(n / 2 - 1);
        }
        return (fibo[n / 2] * fibo[n / 2] + 2 * fibo[n / 2] * fibo[n / 2 - 1]) % 1000000007;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    long long n;
    std::cin >> n;


    std::cout << fibonacci(n) << "\n";

    return 0;
}
