#include <bits/stdc++.h>
using namespace std;


class Solution {
public:
    string reverseWords(string s) {
        stringstream ss(s);
        string word;
        stack<string> st;
        while (ss >> word) {
            st.push(word);
        }
        string ans;
        while (!st.empty()) {
            ans += st.top() + " ";
            st.pop();
        }
        ans.pop_back();
        return ans;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;

    





    return 0;
}