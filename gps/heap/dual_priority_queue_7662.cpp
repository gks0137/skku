#include <iostream>
#include <unordered_map>
using namespace std;

struct _max_heap
{
    int data[1000001];
    int size = 0;
    void push(int x)
    {
        size++;
        data[size] = x;
        int now = size;
        while (now > 1 && data[now / 2] < data[now])
        {
            swap(data[now / 2], data[now]);
            now /= 2;
        }
    }
    void pop()
    {
        if (size == 0)
            return;
        data[1] = data[size];
        size--;
        int now = 1;
        while (now * 2 <= size)
        {
            int next = now * 2;
            if (next + 1 <= size && data[next] < data[next + 1])
                next++;
            if (data[now] >= data[next])
                break;
            swap(data[now], data[next]);
            now = next;
        }
    }
    void clear()
    {
        size = 0;
    }
};

struct _min_heap
{
    int data[1000001];
    int size = 0;
    void push(int x)
    {
        size++;
        data[size] = x;
        int now = size;
        while (now > 1 && data[now / 2] > data[now])
        {
            swap(data[now / 2], data[now]);
            now /= 2;
        }
    }
    void pop()
    {
        if (size == 0)
            return;
        data[1] = data[size];
        size--;
        int now = 1;
        while (now * 2 <= size)
        {
            int next = now * 2;
            if (next + 1 <= size && data[next] > data[next + 1])
                next++;
            if (data[now] <= data[next])
                break;
            swap(data[now], data[next]);
            now = next;
        }
    }
    void clear()
    {
        size = 0;
    }
};

struct _dual_priority_queue
{
    _max_heap* max_heap = new _max_heap();
    _min_heap* min_heap = new _min_heap();
    unordered_map<int, int> count;
    int valid_elements = 0;
    void push(int x)
    {
        max_heap->push(x);
        min_heap->push(x);
        count[x]++;
        valid_elements++;
    }
    void pop_max()
    {
        while (1) {
            if (max_heap->size == 0)
                return;
            int x = max_heap->data[1];
            if (count[x] > 0)
            {
                count[x]--;
                valid_elements--;
                max_heap->pop();
                break;
            }
            else
                max_heap->pop();
        }
    }
    void pop_min()
    {
        while (1) {
            if (min_heap->size == 0)
                return;
            int x = min_heap->data[1];
            if (count[x] > 0)
            {
                count[x]--;
                valid_elements--;
                min_heap->pop();
                break;
            }
            else
                min_heap->pop();
        }
    }

    pair<int, int> get_min_max()
    {
        int max_val = -1, min_val = -1;
        while (max_heap->size > 0)
        {
            int x = max_heap->data[1];
            if (count[x] > 0)
            {
                max_val = x;
                break;
            }
            else
                max_heap->pop();
        }
        while (min_heap->size > 0)
        {
            int x = min_heap->data[1];
            if (count[x] > 0)
            {
                min_val = x;
                break;
            }
            else
                min_heap->pop();
        }
        return {min_val, max_val};
    }

    ~_dual_priority_queue()
    {
        delete max_heap;
        delete min_heap;
    }
};










int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int t;
    std::cin >> t;

    while(t--) {
        _dual_priority_queue* dpq = new _dual_priority_queue();
        int k;
        std::cin >> k;
        while(k--) {
            char c;
            int x;
            std::cin >> c >> x;
            if (c == 'I')
                dpq->push(x);
            else if (c == 'D' && x == 1)
                dpq->pop_max();
            else if (c == 'D' && x == -1)
                dpq->pop_min();
        }

        if (dpq->valid_elements == 0)
            std::cout << "EMPTY\n";
        else {
            pair<int, int> min_max = dpq->get_min_max();
            std::cout << min_max.second << " " << min_max.first << "\n";
        }
        delete dpq;
    }

    return 0;
}
