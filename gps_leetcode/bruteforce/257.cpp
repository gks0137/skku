

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


class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        
        function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string before){
            string curpath = before.empty() ? to_string(node->val) : before + "->" + to_string(node->val);
            if (node->left) dfs(node->left, curpath);
            if (node->right) dfs(node->right, curpath);
            if (!node->left && !node->right) paths.push_back(curpath);
        };

        if (root) dfs(root, "");
        return paths;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    TreeNode* root = new TreeNode(1, new TreeNode(2, nullptr, new TreeNode(5)), new TreeNode(3));
    vector<string> res = sol.binaryTreePaths(root);
    for (const string& path : res) {
        cout << path << "\n";
    }



    return 0;
}