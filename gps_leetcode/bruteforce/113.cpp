

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

    void backtrack(TreeNode* node, int targetSum, vector<int>& current, vector<vector<int>>& paths) {
        if (!node) return;
        current.push_back(node->val);
        if (!node->left && !node->right && node->val == targetSum) {
            paths.push_back(current);
        } else {
            backtrack(node->left, targetSum - node->val, current, paths);
            backtrack(node->right, targetSum - node->val, current, paths);
        }
        current.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> paths;
        vector<int> current;
        backtrack(root, targetSum, current, paths);
        return paths;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    TreeNode* t1 = new TreeNode(5, new TreeNode(4, new TreeNode(11, new TreeNode(7), new TreeNode(2)), nullptr), new TreeNode(8, new TreeNode(13), new TreeNode(4, new TreeNode(5), new TreeNode(1))));
    int targetSum = 22;
    vector<vector<int>> res = sol.pathSum(t1, targetSum);
    for (const auto& path : res) {
        cout << "[";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }


    return 0;
}