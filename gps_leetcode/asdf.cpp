#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> merged;
        bool inserted = false;

        for (const auto& interval : intervals) {
            if (!inserted && newInterval[1] < interval[0]) {
                merged.push_back(newInterval);
                inserted = true;
            }
            if (interval[1] < newInterval[0] || interval[0] > newInterval[1]) {
                merged.push_back(interval);
            } else {
                newInterval[0] = min(newInterval[0], interval[0]);
                newInterval[1] = max(newInterval[1], interval[1]);
            }
        }

        if (!inserted) {
            merged.push_back(newInterval);
        }

        return merged;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    vector<vector<int>> intervals = {{1,3},{6,9}};
    vector<int> newInterval = {2,5};
    vector<vector<int>> result = sol.insert(intervals, newInterval);
    for (const auto& interval : result) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    cout << endl;

    return 0;
}