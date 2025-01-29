#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
    vector<int> heap;

    void heapifyUp(int index) {
        if (index == 0) return; // Root node, no parent
        int parent = (index - 1) / 2;
        if (heap[parent] < heap[index]) {
            swap(heap[parent], heap[index]);
            heapifyUp(parent); // Recur for the parent
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[largest], heap[index]);
            heapifyDown(largest); // Recur for the largest
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    void decreaseKey(int index, int newVal) {
        heap[index] = newVal;
        heapifyDown(index);  // Restore heap property
    }

    void deleteKey(int index) {
        heap[index] = heap.back();
        heap.pop_back();
        heapifyDown(index);  // Restore heap property
    }

    void buildHeap(vector<int>& arr) {
        heap = arr;
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }
    int extractMax() {
        if (heap.empty()) {
            cout << "Heap is empty!" << endl;
            return -1;
        }
        int maxVal = heap[0];  // Root is the maximum value
        heap[0] = heap.back(); // Replace root with last element
        heap.pop_back();       // Remove the last element
        heapifyDown(0);        // Restore heap property
        return maxVal;
    }

    void display() {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap h;
    h.insert(3);
    h.insert(10);
    h.insert(5);
    h.insert(6);
    h.insert(7);
    h.insert(20);
    h.insert(1);

    cout << "Heap elements: ";
    h.display();

    cout << "Extracted max: " << h.extractMax() << endl;
    cout << "Heap after extraction: ";
    h.display();

    MaxHeap h2;

    vector<int> arr2 = {3, 10, 5, 6, 7, 20, 1};
    h2.buildHeap(arr2);

    cout << "Built Heap: ";
    h2.display();

    h2.decreaseKey(2, 4); // Decrease key at index 2 to 4
    cout << "Heap after decreaseKey(2, 4): ";
    h2.display();

    h.deleteKey(3); // Delete key at index 3
    cout << "Heap after deleteKey(3): ";
    h.display();


    return 0;
}
