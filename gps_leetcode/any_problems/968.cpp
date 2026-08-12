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
    int minCameraCover(TreeNode* root) {
        if (!root) return 0;
        
        function<pair<int, int>(TreeNode*)> dfs = [&](TreeNode* node) {
            if (!node) return make_pair(0, 2); // (cameras, state) where state: 0 = not monitored, 1 = monitored, 2 = has camera
            if (!node->left && !node->right) {
                return make_pair(0, 0);
            }
            auto left = dfs(node->left);
            auto right = dfs(node->right);
            int cameras = left.first + right.first;
            int is_child_monitored = min(left.second, right.second);
            if (is_child_monitored == 2) {
                return make_pair(cameras, 1);
            } else if (is_child_monitored == 1) {
                if (max(left.second, right.second) == 1) {
                    return make_pair(cameras, 0);
                } else {
                    if (left.second == 2 && right.second == 2) {
                        return make_pair(cameras, 1);
                    } else if (!node->left || !node->right) {
                        return make_pair(cameras, 0);
                    } else {
                        return make_pair(cameras, 1);
                    }
                }
            } else {
                return make_pair(cameras + 1, 2);
            }
        };

        auto result = dfs(root);
        return result.second == 0 ? result.first + 1 : result.first;

    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    return 0;
}