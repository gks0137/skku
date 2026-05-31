#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        sort(candidates.begin(), candidates.end());

        function<void(int, int)> backtrack = [&](int start, int sum) {
            if (sum == target) {
                res.push_back(path);
                return;
            }
            for (int i = start; i < candidates.size(); ++i) {
                if (i > start && candidates[i] == candidates[i - 1]) continue; // skip duplicates
                if (sum + candidates[i] > target) break; // early stopping
                path.push_back(candidates[i]);
                backtrack(i + 1, sum + candidates[i]); // move to the next index
                path.pop_back();
            }
        };
        backtrack(0, 0);
        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;
    vector<vector<int>> result = sol.combinationSum2(candidates, target);
    for (const auto& combination : result) {
        for (int num : combination) {
            cout << num << " ";
        }
        cout << endl;
    }

    return 0;
}