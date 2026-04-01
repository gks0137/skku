#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;
    std::vector<int> sequence(n);
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        sequence[i] = num;
    }

    std::vector<int> LIS;
    
    for (int i = 0; i < n; ++i) {
        int num;
        num = sequence[n-1-i];
        

        if (LIS.empty() || LIS.back() < num) {
            LIS.push_back(num);
        } else {
            auto it = std::lower_bound(LIS.begin(), LIS.end(), num);
            *it = num;
        }
    }

    int length = LIS.size();

    std::cout << length << "\n";

    return 0;
}
