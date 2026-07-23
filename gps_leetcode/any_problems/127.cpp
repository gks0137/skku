#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) {
            return 0;
        }

        queue<string> q;
        q.push(beginWord);
        int length = 1;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string currentWord = q.front();
                q.pop();

                if (currentWord == endWord) {
                    return length;
                }

                for (int j = 0; j < currentWord.length(); ++j) {
                    char originalChar = currentWord[j];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == originalChar) continue;
                        currentWord[j] = c;

                        if (wordSet.find(currentWord) != wordSet.end()) {
                            q.push(currentWord);
                            wordSet.erase(currentWord);
                        }
                    }
                    currentWord[j] = originalChar;
                }
            }
            ++length;
        }

        return 0;
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