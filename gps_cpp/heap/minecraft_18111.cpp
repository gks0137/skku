#include <iostream>
#include <vector>
using namespace std;

int n, m, b;
vector<vector<int>> world;


int get_time(int height) {
    int time = 0, inventory = b;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (world[i][j] > height) {
                time += 2 * (world[i][j] - height);
                inventory += world[i][j] - height;
            } else if (world[i][j] < height) {
                time += height - world[i][j];
                inventory -= height - world[i][j];
            }
        }
    }
    if (inventory < 0) {
        return -1;
    }
    return time;
}

struct heap_min {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first > b.first;
    }
    vector<pair<int, int>> data = {{0, 0}};
    int size = 0;
    void push(int time, int height) {
        data.push_back({time, height});
        size++;
        int idx = size;
        while (idx > 1) {
            int parent = idx / 2;
            if (operator()(data[parent], data[idx])) {
                swap(data[parent], data[idx]);
                idx = parent;
            } else {
                break;
            }
        }
    }
};





int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    std::cin >> n >> m >> b;
    world.resize(n, vector<int>(m));

    int height_low = 256, height_high = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int height;
            std::cin >> height;
            world[i][j] = height;
            height_low = min(height_low, height);
            height_high = max(height_high, height);
        }
    }

    heap_min* min_heap = new heap_min();

    for (int height = height_low; height <= height_high; height++) {
        int time = get_time(height);
        if (time != -1) {
            min_heap->push(time, height);
        }
    }
    std::cout << min_heap->data[1].first << " " << min_heap->data[1].second << "\n";
    delete min_heap;






    return 0;
}