#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<pair<int, int>> projects;
        for (int i = 0; i < profits.size(); i++) {
            projects.push_back({capital[i], profits[i]});
        }
        sort(projects.begin(), projects.end());
        priority_queue<int> pq;
        int w_cur = w;
        int i = 0;

        for (int j = 0; j < k; j++) {
            while (i < projects.size() && projects[i].first <= w_cur) {
                pq.push(projects[i].second);
                i++;
            }
            if (pq.empty()) break;
            w_cur += pq.top();
            pq.pop();
        }

        return w_cur;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    




    return 0;
}