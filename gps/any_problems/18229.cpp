#include <iostream>
#include <vector>

#define IGNORE 999999

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> a(n, 0);
    for (int i = 0; i < n; ++i) {
        int j;
        for (j = 0; j < m; ++j) {
            int x;
            std::cin >> x;
            a[i] += x;

            if (a[i] >= k) {
                for (int l = j + 1; l < m; ++l) {
                    int x;
                    std::cin >> x;
                }
                break;
            }
        }
        if (a[i] < k) {
            a[i] = IGNORE;
        } else {
            a[i] = j + 1;
        }
        

    }
    // for (int i = 0; i < n; ++i) {
    //     std::cout << a[i] << " ";
    // }

    int min = IGNORE;
    int idx = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] < min) {
            min = a[i];
            idx = i;
        }
    }
    
    std::cout << idx + 1 << " " << min;
    

    return 0;
}