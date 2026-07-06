#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int findTheWinner(int n, int k) {
        deque<int> dq;
        for (int i = 1; i <= n; i++) {
            dq.push_back(i);
        }
        n--;
        while (n--) {
            for (int i = 0; i < k - 1; i++) {
                dq.push_back(dq.front());
                dq.pop_front();
            }
            dq.pop_front();
        }
        return dq.front();
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    





    return 0;
}