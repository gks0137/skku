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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        swap(root->left, root->right);
        if (root->left) invertTree(root->left);
        if (root->right) invertTree(root->right);
        return root;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    TreeNode* subtree1 = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    TreeNode* subtree2 = new TreeNode(7, new TreeNode(6), new TreeNode(9));
    TreeNode* root = new TreeNode(4, subtree1, subtree2);
    sol.invertTree(root);
    cout << root->val << " " << root->left->val << " " << root->right->val << "\n";
    cout << root->left->val << " " << root->left->left->val << " " << root->left->right->val << "\n";
    cout << root->right->val << " " << root->right->left->val << " " << root->right->right->val << "\n";


    return 0;
}