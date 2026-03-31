#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, k;
    std::cin >> n >> k;

    std::deque<std::deque<int>> increasing;

    for (int i=0; i<n; i++) {
        int num;
        std::cin >> num;

        if (increasing.empty()) {
            increasing.push_back({num});
            continue;
        }
        if (increasing.back().front() < num) {
            increasing.push_back({num});
            continue;
        }


        int low=0, high=increasing.size(), mid;
        while (low <= high)
        {
            mid = (low + high) / 2;

            if (increasing[mid][0]==num) {
                break;
            } else if (increasing[mid][0] < num) {
                low = mid + 1;
            } else {
                high = mid-1;
            }
        }
        if (increasing[mid][0] == num) continue;
        if (increasing[mid][0] > num ) mid--;
        if (mid<0) {
            increasing.push_front({num});
            continue;
        }

        int low=0, high=increasing.size(), mid2;
        while (low <= high)
        {
            mid2 = (low + high) / 2;

            if (increasing[mid][0]==num) {
                break;
            } else if (increasing[mid][0] < num) {
                low = mid2 + 1;
            } else {
                high = mid2-1;
            }
        }
        if (increasing[mid][mid2] > num) mid2--;

        increasing[mid].emplace(increasing[mid].begin()+mid2, num);

    }




    return 0;
}