#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        unordered_set<string> Dict(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<int>> memo;

        function<void(int)> spread = [&](int idx) {
            for (int len : memo[idx]) {
                int temp = idx + len;
                if (!dp[temp]) {
                    dp[temp] = true;
                    spread(temp);
                }
            }
        };

        for (const string& word : Dict) {
            int idx = s.find(word);
            while (idx != string::npos) {
                if (dp[idx]) {
                    int temp = idx + word.size();
                    dp[temp] = true;
                    spread(temp);
                } else {
                    memo[idx].push_back(word.size());
                }
                idx = s.find(word, idx + 1);
            }
        }
        return dp[s.size()];
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<string> wordDict = {"aaaa", "baa"};
    string s = "baaaaaa";
    cout << sol.wordBreak(s, wordDict) << "\n";

    return 0;
}