#include <iostream>
#include <vector>
using namespace std;

int findZ(int n, int r, int c) {
    if (n == 0) return 0;

    int half = 1 << (n - 1);
    int quadrant_size = half * half;

    if (r < half && c < half) {
        return findZ(n - 1, r, c);
    } else if (r < half && c >= half) {
        return quadrant_size + findZ(n - 1, r, c - half);
    } else if (r >= half && c < half) {
        return 2 * quadrant_size + findZ(n - 1, r - half, c);
    } else {
        return 3 * quadrant_size + findZ(n - 1, r - half, c - half);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, r, c;
    cin >> n >> r >> c;

    cout << findZ(n, r, c) << "\n";

    return 0;
}