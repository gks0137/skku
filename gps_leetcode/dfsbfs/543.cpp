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
    int maxDiameter = 0;

    void updatedepth(TreeNode* node) {
        if (!node) return;
        updatedepth(node->left);
        updatedepth(node->right);
        int leftDepth = node->left ? node->left->val : 0;
        int rightDepth = node->right ? node->right->val : 0;
        node->val = max(leftDepth, rightDepth) + 1;
        maxDiameter = max(maxDiameter, leftDepth + rightDepth);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        updatedepth(root);
        return maxDiameter;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    TreeNode* subtree1 = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    TreeNode* subtree2 = new TreeNode(7, new TreeNode(6), new TreeNode(9));
    TreeNode* root = new TreeNode(4, subtree1, subtree2);
    cout << sol.diameterOfBinaryTree(root) << "\n";

    return 0;
}