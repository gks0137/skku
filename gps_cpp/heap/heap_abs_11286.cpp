#include <iostream>
using namespace std;

struct heap_abs
{
    int data[100001];
    int size = 0;

    bool abs_less(int a, int b)
    {
        if (abs(a) == abs(b))
            return a < b;
        return abs(a) < abs(b);
    }

    void push(int x)
    {
        data[++size] = x;
        int idx = size;
        while (idx > 1 && abs_less(data[idx], data[idx / 2]))
        {
            std::swap(data[idx], data[idx / 2]);
            idx /= 2;
        }
    }

    int pop()
    {
        if (size == 0)
            return 0;
        int ret = data[1];
        data[1] = data[size--];
        int idx = 1;
        while (true)
        {
            int left = idx * 2, right = idx * 2 + 1, smallest = idx;
            if (left <= size && abs_less(data[left], data[smallest]))
                smallest = left;
            if (right <= size && abs_less(data[right], data[smallest]))
                smallest = right;
            if (smallest == idx)
                break;
            std::swap(data[idx], data[smallest]);
            idx = smallest;
        }
        return ret;
    }
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n;
    std::cin >> n;

    heap_abs* heap = new heap_abs();
    
    for (int i = 0; i < n; ++i)
    {
        int x;
        std::cin >> x;
        if (x == 0)
            std::cout << heap->pop() << '\n';
        else
            heap->push(x);
    }

    
    delete heap;
    return 0;
}
