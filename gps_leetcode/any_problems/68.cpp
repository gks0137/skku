#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int i = 0;

        while (i < n) {
            int j = i;
            int lineLength = 0;

            // Determine how many words can fit in the current line
            while (j < n && lineLength + words[j].length() + (j - i) <= maxWidth) {
                lineLength += words[j].length();
                j++;
            }

            int numWords = j - i;
            int totalSpaces = maxWidth - lineLength;
            string line;

            if (numWords == 1 || j == n) {
                // Left justify for the last line or a single word
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) {
                        line += " ";
                    }
                }
                line += string(maxWidth - line.length(), ' '); // Fill remaining spaces
            } else {
                // Fully justify the line
                int spacesBetweenWords = totalSpaces / (numWords - 1);
                int extraSpaces = totalSpaces % (numWords - 1);

                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) {
                        line += string(spacesBetweenWords + (k - i < extraSpaces ? 1 : 0), ' ');
                    }
                }
            }

            result.push_back(line);
            i = j; // Move to the next set of words
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
    int maxWidth = 16;
    vector<string> result = sol.fullJustify(words, maxWidth);

    for (const string& line : result) {
        cout << "\"" << line << "\"" << endl;
    }

    return 0;
}