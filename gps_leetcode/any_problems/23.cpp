#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        struct max_heap_cmp {
            bool operator()(const ListNode* a, const ListNode* b) const {
                return a->val > b->val;
            }
        };
        priority_queue<ListNode*, vector<ListNode*>, max_heap_cmp> heap;

        for (auto list : lists) {
            if (list) {
                heap.push(list);
            }
        }

        ListNode* result = nullptr;
        ListNode* result_tail = nullptr;

        while (!heap.empty()) {
            ListNode* current = heap.top();
            heap.pop();

            if (!result) {
                result = current;
                result_tail = result;
            } else {
                result_tail->next = current;
                result_tail = result_tail->next;
            }

            if (current->next) {
                heap.push(current->next);
            }
        }

        return result;
    }
};

                

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Solution sol;


    vector<ListNode*> lists;
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);
    lists.push_back(l1);
    lists.push_back(l2);
    lists.push_back(l3);

    auto ans = sol.mergeKLists(lists);
    while (ans) {
        cout << ans->val << " ";
        ans = ans->next;
    }

    return 0;
}