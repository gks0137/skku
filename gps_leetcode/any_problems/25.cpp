#include <bits/stdc++.h>
using namespace std;


struct ListNode {
    const int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k <= 1) return head;
        deque<ListNode*> nodes;
        ListNode* curr = head;
        for (int i = 0; i < k && curr; i++) {
            nodes.push_back(curr);
            curr = curr->next;
        }
        ListNode* newHead = nodes[k-1];
        int idx = 0;
        ListNode* idxNode = head;
        ListNode* temp = head;
        while (idxNode) {
            int idx_mod_k = idx % k;
            if (idx_mod_k == 0) {
                //pop
                if (idx != 0) {
                    for (int i = 0; i < k; i++) {
                        nodes.pop_front();
                    }
                }
                if (nodes.size() < k) {
                    break;
                }
                //push
                for (int i = 0; i < k && curr; i++) {
                    nodes.push_back(curr);
                    curr = curr->next;
                }
                //assign
                if (nodes.size() == 2*k) {
                    temp = idxNode->next;
                    idxNode->next = nodes[2*k-1];
                    idxNode = temp;
                } else {
                    if (nodes.size() > k) {
                        temp = idxNode->next;
                        idxNode->next = nodes[k];
                        idxNode = temp;
                    } else {
                        temp = idxNode->next;
                        idxNode->next = nullptr;
                        idxNode = temp;
                    }
                }
            } else {
                temp = idxNode->next;
                idxNode->next = nodes[idx_mod_k-1];
                idxNode = temp;
            }
            idx++;
        }
        return newHead;

    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    int k = 2;

    head = sol.reverseKGroup(head, k);
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }

    return 0;
}