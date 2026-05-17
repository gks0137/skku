#include <bits/stdc++.h>
using namespace std;

class Fancy {
private:
    vector<int> values;
    int idx_start;
    long long add_val = 0;
    long long mult_val = 1;
    Fancy* next = nullptr;
public:
    Fancy() : values(), idx_start(0), add_val(0), mult_val(1), next(nullptr) {}
    Fancy(int val1, int idx) : values({val1}), idx_start(idx), add_val(0), mult_val(1), next(nullptr) {}
    
    void append(int val) {
        if (next) {
            next->append(val);
        } else if (add_val != 0 || mult_val != 1) {
            next = new Fancy(val, idx_start + values.size());
        } else {
            values.push_back(val);
        }
    }
    
    void addAll(int inc) {
        if (next) {
            next->addAll(inc);
        } else {
            add_val += inc;
            add_val %= 1000000007;
        }
    }
    
    void multAll(int m) {
        if (next) {
            next->multAll(m);
        } else {
            add_val = (add_val * m) % 1000000007;
            mult_val = (mult_val * m) % 1000000007;
        }
    }

    void lazy_update(Fancy* node, long long& value) {
        value = (value * node->mult_val) % 1000000007;
        value = (value + node->add_val) % 1000000007;
        if (node->next) {
            lazy_update(node->next, value);
        }
    }
    
    
    int getIndex(int idx) {
        if (idx >= idx_start + values.size()) {
            if (next) {
                return next->getIndex(idx);
            } else {
                return -1;
            }
        } else {
            long long val = values[idx - idx_start];
            lazy_update(this, val);
            return val;
        }
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    
    vector<string> operations = {"Fancy","append","addAll","append","multAll","getIndex","addAll","append","multAll","getIndex","getIndex","getIndex"};
    vector<vector<int>> values = {{},{2},{3},{7},{2},{0},{3},{10},{2},{0},{1},{2}};
    Fancy* obj = nullptr;
    for (int i = 0; i < operations.size(); i++) {
        if (operations[i] == "Fancy") {
            obj = new Fancy();
        } else if (operations[i] == "append") {
            obj->append(values[i][0]);
        } else if (operations[i] == "addAll") {
            obj->addAll(values[i][0]);
        } else if (operations[i] == "multAll") {
            obj->multAll(values[i][0]);
        } else if (operations[i] == "getIndex") {
            cout << obj->getIndex(values[i][0]) << "\n";
        }
    }

    return 0;
}   
