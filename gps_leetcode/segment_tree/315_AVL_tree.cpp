#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Node {
        int val;
        int count;  // total number of nodes in this subtree
        int dup;    // count of duplicate values at this node
        int height; // height of subtree
        Node* left;
        Node* right;
        
        Node(int v) : val(v), count(1), dup(1), height(1), left(nullptr), right(nullptr) {}
    };
    
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    
    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
    }
    
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    // Right rotation
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        updateHeight(y);
        updateHeight(x);
        
        // Update count after rotation
        y->count = (y->left ? y->left->count : 0) + (y->right ? y->right->count : 0) + y->dup;
        x->count = (x->left ? x->left->count : 0) + (x->right ? x->right->count : 0) + x->dup;
        
        return x;
    }
    
    // Left rotation
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        updateHeight(x);
        updateHeight(y);
        
        // Update count after rotation
        x->count = (x->left ? x->left->count : 0) + (x->right ? x->right->count : 0) + x->dup;
        y->count = (y->left ? y->left->count : 0) + (y->right ? y->right->count : 0) + y->dup;
        
        return y;
    }
    
    // Insert val into AVL BST and return count of smaller elements
    int insert(Node*& node, int val) {
        if (!node) {
            node = new Node(val);
            return 0;
        }
        
        int result = 0;
        
        if (val < node->val) {
            // Go left, no elements counted on right
            result = insert(node->left, val);
        } else if (val > node->val) {
            // Count: all elements in left subtree + current node's duplicates
            result = (node->left ? node->left->count : 0) + node->dup;
            result += insert(node->right, val);
        } else {
            // val == node->val: count only left subtree
            result = node->left ? node->left->count : 0;
            node->dup++;
        }
        
        // Update count and height of current subtree
        node->count = (node->left ? node->left->count : 0) + (node->right ? node->right->count : 0) + node->dup;
        updateHeight(node);
        
        // Balance the tree
        int balance = getBalance(node);
        
        // Left heavy
        if (balance > 1) {
            if (val < node->left->val) {
                // Left-Left case
                node = rotateRight(node);
            } else {
                // Left-Right case
                node->left = rotateLeft(node->left);
                node = rotateRight(node);
            }
        }
        
        // Right heavy
        if (balance < -1) {
            if (val > node->right->val) {
                // Right-Right case
                node = rotateLeft(node);
            } else {
                // Right-Left case
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
            }
        }
        
        return result;
    }
    
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result(nums.size());
        Node* root = nullptr;
        
        // Traverse from right to left
        for (int i = nums.size() - 1; i >= 0; --i) {
            result[i] = insert(root, nums[i]);
        }
        
        return result;
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<int> nums = {5, 2, 6, 1, 1};
    vector<int> result = sol.countSmaller(nums);
    for (int res : result) {
        cout << res << " ";
    }



    return 0;
}   
