#include <iostream>
#include <deque>
#include <vector>
#include <cmath>

int N, K;


// int f_approx(int t) {
//     if (t < N) {
//         float temp = log(t) * t;
//         return t + (int)floor(temp);
//     } else {
//         float temp = log((float)N*N/t) * t;
//         return t + (int)floor(temp);
//     }
// }

int f_abs(int t) {
    int result = 0;
    int high = std::min(N, t);
    for (int i = 1; i <= high; i++) {
        result += std::min(N, t/i);
    }
    return result;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> K;
    
    int low = 1, high = K, mid, temp;
    while (low < high) {
        mid = low + (high - low) / 2;
        temp = f_abs(mid);
        if (temp < K) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    
    std::cout << low << "\n";





    // int t_temp = low;
    // while (f_abs(t_temp) < K) {
    //     t_temp++;
    // }
    // std::cout << t_temp << "\n";






    return 0;
}