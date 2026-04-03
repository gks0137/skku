#include <iostream>
#include <vector>
#include <cmath>

int n;

int count_least_Squares(int num, int depth) {
    if (num < 0) {
        return 4;
    }
    if (num == 0 || depth == 4) {
        return depth;
    }
    int least = 4;
    int start = (int)std::sqrt(num/2), end = (int)std::sqrt(num);
    for (int i = start; i <= end; i++) {
        least = std::min(least, count_least_Squares(num - i * i, depth + 1));
    }
    return least;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n;
    std::cin >> n;
    std::cout << count_least_Squares(n, 0) << "\n";
    

    return 0;
}
