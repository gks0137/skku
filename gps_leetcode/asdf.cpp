#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    string simplifyPath(string path) {
        stack<string> st;
        stringstream ss(path);
        string token;
        while (getline(ss, token, '/')) {
            if (token == "" || token == ".") {
                continue;
            } else if (token == "..") {
                if (!st.empty()) {
                    st.pop();
                }
            } else {
                st.push(token);
            }
        }
        if (st.empty()) {
            return "/";
        } else {
            string res;
            while (!st.empty()) {
                res = "/" + st.top() + res;
                st.pop();
            }
            return res;
        }
    }
};





int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    return 0;
}