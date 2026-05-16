#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    struct Node {
        int start, end, max_height, lazy=0;
        Node* left;
        Node* right;
        Node(int s, int e, int h) : start(s), end(e), max_height(h), lazy(0), left(nullptr), right(nullptr) {}
    };

    void propagate(Node* node) {
        if (node->lazy) {
            node->max_height = node->lazy;
            if (node->left) {
                node->left->max_height = node->lazy;
                node->left->lazy = node->lazy;
            }
            if (node->right) {
                node->right->max_height = node->lazy;
                node->right->lazy = node->lazy;
            }
            node->lazy = 0;
        }
    }

    void update(Node* node, int& left, int& right, int& height) {
        if (node->end < left || node->start > right) {
            return;
        }
        if (node->start >= left && node->end <= right) {
            // cout << "Updating node [" << node->start << ", " << node->end << "] from height " << node->max_height << " to " << node->max_height + height << "\n";
            node->max_height += height;
            node->lazy = node->max_height;
            return;
        }
        int mid = node->start + (node->end - node->start) / 2;
        if (!node->left) {
            node->left = new Node(node->start, mid, node->max_height);
            node->right = new Node(mid + 1, node->end, node->max_height);
        }
        propagate(node);
        update(node->left, left, right, height);
        update(node->right, left, right, height);
        node->max_height = max(node->left->max_height, node->right->max_height);
    }

    void lazy_update(Node* node, int& left, int& right, int& max_height) {
        if (node->end < left || node->start > right) {
            return;
        }
        if (node->start >= left && node->end <= right) {
            node->max_height = max_height;
            node->lazy = max_height;
            return;
        }
        lazy_update(node->left, left, right, max_height);
        lazy_update(node->right, left, right, max_height);
    }

    int find_max_height(Node* node, int& left, int& right) {
        if (node->end < left || node->start > right) {
            return 0;
        }
        if (node->start >= left && node->end <= right) {
            return node->max_height;
        }
        return max(find_max_height(node->left, left, right), find_max_height(node->right, left, right));
    }

    vector<int> fallingSquares(vector<vector<int>>& positions) {
        Node* root = new Node(1, 1e9, 0);
        vector<int> result;
        for (const auto& pos : positions) {
            int left = pos[0];
            int side = pos[1];
            int right = left + side - 1;
            update(root, left, right, side);
            int recent = find_max_height(root, left, right);
            lazy_update(root, left, right, recent);
            result.push_back(root->max_height);
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<vector<int>> positions = {{9, 6}, {2, 2}, {2, 6}};
    vector<vector<int>> positions2 = {{100, 100}, {200, 100}};
    vector<int> result = sol.fallingSquares(positions);
    for (int height : result) {
        cout << height << " ";
    }



    return 0;
}   
