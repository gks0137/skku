#include <iostream>
#include <algorithm>
#include <vector>
    
std::vector<int> lengths;

long long get_cut_wood(int cut_length) {
    long long total_cut = 0;
    for (int length : lengths) {
        if (length > cut_length) {
            total_cut += (length - cut_length);
        }
    }
    return total_cut;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n, m;
    std::cin >> n >> m;
    lengths.resize(n);
    int max_length = 0;

    for (int i = 0; i < n; ++i) {
        int length;
        std::cin >> length;
        lengths[i] = length;
        if (length > max_length) {
            max_length = length;
        }
    }

    int left = 0, right = max_length;
    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long cut_wood = get_cut_wood(mid);

        if (cut_wood >= m) {
            result = mid; // 가능한 최대 절단 길이
            left = mid + 1; // 더 긴 절단 길이를 시도
        } else {
            right = mid - 1; // 더 짧은 절단 길이를 시도
        }
    }

    std::cout << result << "\n";

    

    return 0;
}
