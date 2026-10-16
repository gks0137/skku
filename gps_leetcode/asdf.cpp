#include <bits/stdc++.h>
using namespace std;

class min_heap {
public:
	vector<int> heap;

	min_heap() {}

	void push(int val) {
		heap.push_back(val);
		int index = heap.size() - 1;
		while (index > 0) {
			int parent = (index - 1) / 2;
			if (heap[parent] <= heap[index]) break;
			swap(heap[parent], heap[index]);
			index = parent;
		}
	}

	void pop() {
		if (heap.empty()) return;
		swap(heap[0], heap.back());
		heap.pop_back();
		int index = 0;
		while (true) {
			int left = 2 * index + 1;
			int right = 2 * index + 2;
			int smallest = index;

			if (left < heap.size() && heap[left] < heap[smallest]) {
				smallest = left;
			}
			if (right < heap.size() && heap[right] < heap[smallest]) {
				smallest = right;
			}
			if (smallest == index) break;
			swap(heap[index], heap[smallest]);
			index = smallest;
		}
	}

	int top() {
		if (heap.empty()) throw runtime_error("Heap is empty");
		return heap[0];
	}

	bool empty() {
		return heap.empty();
	}

	void build_heap(const vector<int>& arr) {
		// Bottom-up heap construction
		heap = arr;
		for (int i = (heap.size() / 2) - 1; i>= 0; --i) {
			int index = i;
			while (true) {
				int left = 2 * index + 1;
				int right = 2 * index + 2;
				int smallest = index;

				if (left < heap.size() && heap[left] < heap[smallest]) {
					smallest = left;
				}
				if (right < heap.size() && heap[right] < heap[smallest]) {
					smallest = right;
				}
				if (smallest == index) break;
				swap(heap[index], heap[smallest]);
				index = smallest;
			}
		}
	}
};