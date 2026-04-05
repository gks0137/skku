#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> sequence(n);
    std::vector<int> LIS;
    std::vector<int> S;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        sequence[i] = num;

        if (LIS.empty() || LIS.back() < num) {
            LIS.push_back(num);
            S.push_back(LIS.size());
        } else {
            auto it = std::lower_bound(LIS.begin(), LIS.end(), num);
            *it = num;
            S.push_back(it - LIS.begin() + 1);
        }
    }

    int length = LIS.size();

    std::cout << length << "\n";

    std::vector<int> result(length);

    int j = length;
    for (int i = S.size() - 1; i >= 0; --i) {
        if (S[i] == j) {
            result[j - 1] = sequence[i];
            --j;
        }
    }

    for (int i = 0; i < length; ++i) {
        std::cout << result[i] << " ";
    }

    return 0;
}
