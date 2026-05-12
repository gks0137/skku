#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.empty()) {
            return result;
        }
        vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        function<void(int, string)> backtrack = [&](int index, string current) {
            if (index == digits.size()) {
                result.push_back(current);
                return;
            }
            int digit = digits[index] - '0';
            for (char c : mapping[digit]) {
                backtrack(index + 1, current + c);
            }
        };
        backtrack(0, "");
        return result;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    string s = "23";
    vector<string> ans = sol.letterCombinations(s);
    for (auto &x : ans) {
        cout << x << ", ";
    }



    return 0;
}