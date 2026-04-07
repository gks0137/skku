#include <iostream>
#include <vector>
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n, m;
    std::cin >> n >> m;
    cin.ignore(); // Ignore the newline after reading m

    vector<int> ioi;
    int count = 0;

    char prev = 'O'; // Initialize to 'O' to handle the first character correctly
    while (m--) {
        char c;
        cin.get(c);
        if (c == 'I') {
            if (prev == 'O') {
                count++;
            } else {
                if (count > 1) {
                ioi.push_back(count/2);
                count = 1; // Start counting the new sequence with the current 'I'
                }
            }
        } else if (c == 'O') {
            if (prev == 'I') {
                count++;
            } else {
                if (count > 1) {
                ioi.push_back((count-1)/2);
                count = 0;
                }
            }
        }
        prev = c;
    }
    if (count > 1) {
        if (prev == 'I') {
            ioi.push_back(count/2);
        } else {
            ioi.push_back((count-1)/2);
        }
    }
    
    int ans = 0;
    for (int x : ioi) {
        //cout << x << " ";
        if (x >= n) {
            ans += x - n + 1;
        }
    }

    std::cout << ans << "\n";

    return 0;
}
