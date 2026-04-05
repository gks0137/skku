#include <iostream>



struct heap_min
{
    int data[100001];
    int size = 0;
};

bool empty(const heap_min* h)
{
    return h->size == 0;
}

void push(heap_min* h, int x)
{
    h->data[++h->size] = x;
    int idx = h->size;
    while (idx > 1 && h->data[idx] < h->data[idx / 2])
    {
        std::swap(h->data[idx], h->data[idx / 2]);
        idx /= 2;
    }
}

void pop(heap_min* h)
{
    if (empty(h))
        return;
    h->data[1] = h->data[h->size--];
    int idx = 1;
    while (true)
    {
        int left = idx * 2, right = idx * 2 + 1, smallest = idx;
        if (left <= h->size && h->data[left] < h->data[smallest])
            smallest = left;
        if (right <= h->size && h->data[right] < h->data[smallest])
            smallest = right;
        if (smallest == idx)
            break;
        std::swap(h->data[idx], h->data[smallest]);
        idx = smallest;
    }
}









int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n;
    std::cin >> n;

    heap_min* h = new heap_min();

    while (n--)
    {
        int x;
        std::cin >> x;
        if (x == 0)
        {
            if (empty(h))
                std::cout << "0\n";
            else
            {
                std::cout << h->data[1] << "\n";
                pop(h);
            }
        }
        else
            push(h, x);
    }

    

    
    delete h;
    return 0;
}
