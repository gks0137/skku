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
    int maxPathSum(TreeNode* root) {
        int max_sum = INT_MIN;

        function<int(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return 0;
            int left = max(0, dfs(node->left));
            int right = max(0, dfs(node->right));
            max_sum = std::max(max_sum, left + right + node->val);
            return std::max(left, right) + node->val;
        };

        dfs(root);
        return max_sum;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    return 0;
}