#include <iostream>
using namespace std;

struct heap
{
    int data[100001];
    int size = 0;
};

void push(heap* h, int x) {
    h->size++;
    h->data[h->size] = x;

    int me = h->size;
    int parent = me / 2;

    while (parent > 0 && h->data[parent] < h->data[me]) {
        swap(h->data[parent], h->data[me]);
        me = parent;
        parent = me/2;
    }
}

bool empty(heap* h) {
    return h->size == 0;
}

void pop(heap* h) {
    if (empty(h)) return;

    h->data[1] = h->data[h->size];
    h->size--;

    int me = 1;
    int left = me*2;
    int right = me*2 + 1;

    while (1) {
        int largest = me;

        if (left <= h->size && h->data[left] > h->data[largest]) {
            largest = left;
        }
        if (right <= h->size && h->data[right] > h->data[largest]) {
            largest = right;
        }
        if (largest == me) {
            break;
        }
        swap(h->data[me], h->data[largest]);
        me = largest;
        left = me * 2;
        right = me * 2 + 1;

    }
}

int top(heap* h) {
    if (empty(h)) return 0;
    return h->data[1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);




    heap h;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (x == 0) {
            cout << top(&h) << "\n";
            pop(&h);
        }
        else {
            push(&h, x);
        }
    }


    return 0;
}