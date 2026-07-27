#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        vector<int> cur;

        function<void(int)> backtrack = [&](int start) {
            result.push_back(cur);
            for (int i = start; i < n; ++i) {
                cur.push_back(nums[i]);
                backtrack(i + 1);
                cur.pop_back();
            }
        };

        backtrack(0);
        return result;
    }
};




int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    string beginWord = "hit", endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    cout << sol.ladderLength(beginWord, endWord, wordList) << endl;

    return 0;
}