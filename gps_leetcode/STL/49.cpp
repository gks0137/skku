#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;

        int idx_max = 0;
        unordered_map<string, int> idxMap;
        for (const string& str : strs) {
            int charCount[1281] = {0};
            for (const char& c : str) {
                charCount[c]++;
            }
            string key;
            for (int i = 97; i < 123; ++i) {
                key += charCount[i];
            }
            int* idxPtr = &idxMap[key];
            if (*idxPtr == 0) {
                *idxPtr = ++idx_max;
                result.push_back({str});
            } else {
                result[*idxPtr - 1].push_back(str);
            }
        }
        return result;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    vector<string> strs = {"bdddddddddd","bbbbbbbbbbc"};
    Solution sol;
    auto result = sol.groupAnagrams(strs);
    for (const auto& group : result) {
        for (const auto& str : group) {
            cout << str << " ";
        }
        cout << "\n";
    }

    return 0;
}