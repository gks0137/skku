#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        deque<pair<int, int>> dq;
        int n = gas.size();
        for (int i = 0; i < n; ++i) {
            dq.push_back({gas[i] - cost[i], i});
        }
        while (dq.size() != 1) {
            auto [diff, idx] = dq.front();
            dq.pop_front();
            if (diff < 0) {
                while (!dq.empty() && dq.front().first < 0) {
                    int next_diff = dq.front().first;
                    dq.pop_front();
                    diff += next_diff;
                }
                dq.push_back({diff, idx});
            } else {
                while (!dq.empty()) {
                    int next_diff = dq.front().first;
                    dq.pop_front();
                    diff += next_diff;
                    if (diff < 0) {
                        break;
                    }
                }
                dq.push_back({diff, idx});
            }
        }
        if (dq.front().first < 0) {
            return -1;
        } else {
            return dq.front().second;
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol;
    

    return 0;
}