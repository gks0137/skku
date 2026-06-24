#include <bits/stdc++.h>
using namespace std;


class Solution {
public: 
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> engineers;
        for (int i = 0; i < n; ++i) {
            engineers.emplace_back(efficiency[i], speed[i]);
        }
        sort(engineers.begin(), engineers.end(), greater<pair<int, int>>());
        

        priority_queue<int, vector<int>, greater<int>> min_heap;
        long long ans = 0;
        long long max_speed_sum = 0;
        for (auto [eff, spd] : engineers) {
            min_heap.push(spd);
            max_speed_sum += spd;
            if (min_heap.size() > k) {
                max_speed_sum -= min_heap.top();
                if (spd == min_heap.top()) {
                    min_heap.pop();
                    continue;
                } else {
                    min_heap.pop();
                }
            }
            ans = max(ans, max_speed_sum * eff);
        }
        

        return ans % 1000000007;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    

    return 0;
}