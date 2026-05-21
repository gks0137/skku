#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int n = s.size() - words.size() * words[0].size() + 1;
        int m = words.size();
        int word_len = words[0].size();
        unordered_map<int, int> idx_word;
        for (int i = 0; i < n; i++) {
            vector<bool> word_used(m, false);
            int j = i;
            while (1) {
                if (idx_word.find(j) != idx_word.end()) {
                    if (word_used[idx_word[j]]) {
                        break;
                    }
                    word_used[idx_word[j]] = true;
                } else {
                    string word = s.substr(j, word_len);
                    auto start = words.begin() + (find(word_used.begin(), word_used.end(), false) - word_used.begin());
                    bool found = false;
                    do {
                        auto it = find(start, words.end(), word);
                        if (it == words.end()) {
                            break;
                        }
                        int idx = it - words.begin();
                        if (word_used[idx]) {
                            start = it + 1;
                            continue;
                        } else {
                            found = true;
                            word_used[idx] = true;
                            idx_word[j] = idx;
                            break;
                        }
                    } while (1);
                    if (!found) {
                        break;
                    }
                }
                j += word_len;
            }
            if (all_of(word_used.begin(), word_used.end(), [](bool used) { return used; })) {
                res.push_back(i);
            }
        }
        return res;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    string s = "barfoothefoobarman";
    vector<string> words = {"foo","bar"};
    vector<int> res = sol.findSubstring(s, words);
    for (int i : res) {
        cout << i << " ";
    }





    return 0;
}