#include <bits/stdc++.h>
using namespace std;

class Tree{
public:
    int size;
    vector<int> data_start;
    vector<int> data_end;
    vector<int> lazy;

    void init(int size) {
        this->size = size;
        this->data_start.resize(4*size);
        this->data_end.resize(4*size);
        this->lazy.resize(4*size);
    }

    void build(int idx, int start, int end) {
        if (start == end) {
            cin >> this->data_start[idx];
            cin >> this->data_end[idx];
            return;
        }
        int mid = start + (end - start) / 2;
        build(idx*2, start, mid);
        build(idx*2+1, mid+1, end);
        this->data_end[idx] = min(this->data_end[idx*2], this->data_end[idx*2+1]);
        this->data_start[idx] = this->data_start[idx*2+1];
        this->lazy[idx*2] = this->data_end[idx];
    }

    void propagate(int idx, bool p) {
        if (!this->lazy[idx]) return;

        int t = min(this->data_end[idx], this->lazy[idx]);
        if (!p) {
            this->lazy[2*idx] = t;
            if (this->data_end[2*idx+1] > t) this->lazy[2*idx+1] = t;
        }
        this->data_end[idx] = t;
        this->lazy[idx] = 0;
    }

    int get(int time, int idx, int start, int end) {
        propagate(idx, start==end);
        if (start == end) {
            if (time > this->data_start[idx]) return 1000000001;
            return this->data_end[idx];
        };
        int mid = start + (end - start) / 2;
        if (time > this->data_start[idx*2]) {
            return get(time, idx*2+1, mid+1, end);
        } else {
            return get(time, idx*2, start, mid);
        }
    }

};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> cls(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> cls[i].first;
        cin >> cls[i].second;
    }
    int cur_cls = 1;
    int max_go = 0;

    Tree* M = new Tree;
    M->init(m);
    M->build(1, 1, m);
    Tree* K = new Tree;
    K->init(k);
    K->build(1, 1, k);


    


    while (cur_cls < n) {
        int cls_end = cls[cur_cls].second;
        int next_cls = cls[cur_cls+1].first;

        int fast = cls_end;
        while (true) {
            int fast_go = M->get(fast, 1, 1, m);
            fast = K->get(fast_go, 1, 1, k);
            if (fast > next_cls) break;
            max_go++;
        }
        
        cur_cls++;

    }
    cout << max_go;
    

    return 0;
}