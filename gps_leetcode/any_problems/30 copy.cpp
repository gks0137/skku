#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int m = words.size();
        int word_len = words[0].size();
        int n = s.size() - m * word_len + 1;
        unordered_map<string, int> hash;
        for (int i = 0; i < m; i++) {
            hash[words[i]]++;
        }

        for (int i = 0; i < word_len; i++) {
            unordered_map<string, int> seen;
            int j = i;
            while (j < n) {
                int k = j, kmax = j + m * word_len;
                if (!seen.empty()) {
                    string word = s.substr(k - word_len, word_len);
                    seen[word]--;
                    if (seen[word] == 0) {
                        seen.erase(word);
                    }
                    k += (m-1) * word_len;
                }
                while (k < kmax) {
                    string word = s.substr(k, word_len);
                    if (hash.find(word) == hash.end()) {
                        j = k + word_len;
                        seen.clear();
                        break;
                    }
                    seen[word]++;
                    if (seen[word] > hash[word]) {
                        j += word_len;
                        seen.clear();
                        break;
                    }
                    k += word_len;
                }
                if (!seen.empty()) {
                    res.push_back(j);
                    j += word_len;
                }

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
    vector<string> words = {"foo","bar", "the"};
    vector<int> res = sol.findSubstring(s, words);
    for (int i : res) {
        cout << i << " ";
    }





    return 0;
}