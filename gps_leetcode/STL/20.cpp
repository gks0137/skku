#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> q;
        for (const char& c : s) {
            if (c == '(' || c == '{' || c == '[') {
                q.push(c);
            } else {
                if (q.empty()) return false;
                char top = q.top();
                if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                    return false;
                }
                q.pop();
            }
        }
        return q.empty();
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    string s = "([{}])";
    Solution sol;
    cout << sol.isValid(s) << "\n";



    return 0;
}