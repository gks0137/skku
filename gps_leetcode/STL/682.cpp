#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calPoints(vector<string>& operations) {
        vector<int> scores;
        for (const string& op : operations) {
            if (op == "C") {
                if (!scores.empty()) {
                    scores.pop_back();
                }
            } else if (op == "D") {
                if (!scores.empty()) {
                    scores.push_back(2 * scores.back());
                }
            } else if (op == "+") {
                int n = scores.size();
                if (n >= 2) {
                    scores.push_back(scores[n - 1] + scores[n - 2]);
                } else if (n == 1) {
                    scores.push_back(scores[0]);
                }
            } else {
                scores.push_back(stoi(op));
            }
        }
        int totalScore = 0;
        for (int score : scores) {
            totalScore += score;
        }
        return totalScore;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    vector<string> operations = {"5","2","C","D","+"};
    Solution sol;
    cout << sol.calPoints(operations) << "\n";



    return 0;
}