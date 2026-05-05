#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<pair<int, int>> sortedIntervals;
        for (const auto& interval : intervals) {
            sortedIntervals.emplace_back(interval[0], 1);
            sortedIntervals.emplace_back(interval[1], -1);
        }
        sort(sortedIntervals.begin(), sortedIntervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) {
                return a.second > b.second; // Start points come before end points
            }
            return a.first < b.first; // Sort by the point value
        });
        vector<vector<int>> merged;
        int activeIntervals = 0;
        int currentStart = 0;
        for (const auto& p : sortedIntervals) {
            if (activeIntervals == 0) {
                currentStart = p.first;
            }
            activeIntervals += p.second;
            if (activeIntervals == 0) {
                merged.push_back({currentStart, p.first});
            }
        }
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