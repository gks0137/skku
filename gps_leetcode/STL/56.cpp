#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<pair<int, int>> sortedIntervals;
        for (const auto& interval : intervals) {
            sortedIntervals.emplace_back(interval[0], interval[1]);
        }
        sort(sortedIntervals.begin(), sortedIntervals.end());
        vector<vector<int>> merged;
        int start = sortedIntervals[0].first;
        int end = sortedIntervals[0].second;
        for (size_t i = 1; i < sortedIntervals.size(); ++i) {
            if (sortedIntervals[i].first <= end) {
                end = max(end, sortedIntervals[i].second);
            } else {
                merged.push_back({start, end});
                start = sortedIntervals[i].first;
                end = sortedIntervals[i].second;
            }
        }
        merged.push_back({start, end});
        return merged;
    }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> ans = merge(intervals);
    
    for (auto& interval : ans) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    




    return 0;
}