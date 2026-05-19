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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        if (root->val == targetSum && !root->left && !root->right) return true;
        if (hasPathSum(root->left, targetSum - root->val)) return true;
        return hasPathSum(root->right, targetSum - root->val);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    TreeNode* subtree1 = new TreeNode(11, new TreeNode(7), new TreeNode(2));
    TreeNode* subtree2 = new TreeNode(8, new TreeNode(13), new TreeNode(4, nullptr, new TreeNode(1)));
    TreeNode* root = new TreeNode(5, new TreeNode(4, subtree1, nullptr), subtree2);
    int targetSum = 22;
    cout << sol.hasPathSum(root, targetSum) << "\n";


    return 0;
}