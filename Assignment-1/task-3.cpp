#include<iostream>
#include<vector>
#include<assert.h>

/************************/
/*    min heap class    */
/************************/
class minHeap {
private:
    int current_idx{-1};
    int capacity{1000};
    int* array{nullptr};

    // Calculate parent index
    int parent(int child_pos) {
        int parent_pos = (child_pos - 1) / 2;
        return child_pos ? parent_pos : -1;
    }

    // Calculate left child index
    int left(int parent_pos) {
        int left_child_pos = (2 * parent_pos) + 1;
        return left_child_pos <= current_idx ? left_child_pos : -1;
    }

    // Calculate right child index
    int right(int parent_pos) {
        int right_child_pos = (2 * parent_pos) + 2;
        return right_child_pos <= current_idx ? right_child_pos : -1;
    }

    // Heapify up operation
    void heapify_up(int child_pos) {
        int parent_pos = parent(child_pos);

        if (!child_pos || array[parent_pos] <= array[child_pos]) {
            return;
        }

        std :: swap(array[parent_pos], array[child_pos]);
        heapify_up(parent_pos);
    }

    // Heapify down operation
    void heapify_down(int parent_pos) {
        int left_child_pos = left(parent_pos), right_child_pos = right(parent_pos);
        int target_pos = left_child_pos;

        // Leaf node
        if (left_child_pos == -1) {
            return;
        }

        // Swap with right child instead of left if necessary
        if (right_child_pos != -1 && array[right_child_pos] < array[left_child_pos]) {
            target_pos = right_child_pos;
        }

        // Swap if target child is less than parent
        if (array[target_pos] < array[parent_pos]) {
            std :: swap(array[target_pos], array[parent_pos]);
            heapify_down(target_pos);
        }
    }

    // Floyd Heapify algorithm (from bottom to up and ignores the leaf nodes)
    void heapify() {
        for (int i = current_idx / 2; i >= 0; i--) {
            heapify_down(i);
        }
    }

public:
    // Constructor
    minHeap() {
        array = new int[capacity];
    }
    
    // Constructor with vector input
    minHeap(const std :: vector<int>& v) {
        int n = v.size();
        array = new int[capacity];

        assert(n <= capacity);

        for (int i = 0; i < n; i++) {
            array[i] = v[i];
        }

        current_idx = n - 1;

        heapify();
    }

    // Insert element into the heap
    void push(const int& data) {
        assert(!full());

        array[++current_idx] = data;
        heapify_up(current_idx);
    }

    // Remove top element from the heap
    void pop() {
        assert(!empty());

        std :: swap(array[0], array[current_idx--]);
        heapify_down(0);
    }

    // Get the top element of the heap
    int top() {
        assert(!empty());
        return array[0];
    }


    // Check if the heap is empty
    bool empty() {
        return current_idx == -1;
    }

    // Check if the heap is full
    bool full() {
        return current_idx == capacity - 1;
    }

    // Destructor
    ~minHeap() {
        delete [] array;
        array = nullptr;
    }
};



/************************/
/*    max heap class    */
/************************/
class maxHeap {
private:
    int current_idx{-1};
    int capacity{1000};
    int* array{nullptr};

    // Calculate parent index
    int parent(int child_pos) {
        int parent_pos = (child_pos - 1) / 2;
        return child_pos ? parent_pos : -1;
    }

    // Calculate left child index
    int left(int parent_pos) {
        int left_child_pos = (2 * parent_pos) + 1;
        return left_child_pos <= current_idx ? left_child_pos : -1;
    }

    // Calculate right child index
    int right(int parent_pos) {
        int right_child_pos = (2 * parent_pos) + 2;
        return right_child_pos <= current_idx ? right_child_pos : -1;
    }

    // Heapify up operation
    void heapify_up(int child_pos) {
        int parent_pos = parent(child_pos);

        if (!child_pos || array[child_pos] < array[parent_pos]) {
            return;
        }

        std :: swap(array[child_pos], array[parent_pos]);
        heapify_up(parent_pos);
    }

    // Heapify down operation
    void heapify_down(int parent_pos) {
        int left_child_pos = left(parent_pos), right_child_pos = right(parent_pos);
        int target_pos = left_child_pos;

        if (left_child_pos == -1) {
            return;
        }

        if (right_child_pos != -1 && array[right_child_pos] > array[left_child_pos]) {
            target_pos = right_child_pos;
        }

        if (array[parent_pos] < array[target_pos]) {
            std :: swap(array[parent_pos], array[target_pos]);
            heapify_down(target_pos);
        }
    }

    // Floyd heapify algorithm (from bottom to up and ignores the leaf nodes)
    void heapify() {
        for (int i = current_idx / 2; i >= 0; i--) {
            heapify_down(i);
        }
    }

public:
    // Constructor
    maxHeap() {
        array = new int[capacity];
    }

    // Constructor with vector input
    maxHeap(const std :: vector<int>& v) {
        int n = v.size();
        assert(n <= capacity);

        array = new int[capacity];

        for (int i = 0; i < n; i++) {
            array[i] = v[i];
        }

        current_idx = n - 1;

        // Fix the entire array
        heapify();
    }

    // Insert element into the heap
    void push(int data) {
        assert(!full());

        array[++current_idx] = data;
        heapify_up(current_idx);
    }

    // Remove top element from the heap
    void pop() {
        assert(!empty());

        std :: swap(array[0], array[current_idx--]);
        heapify_down(0);
    }

    // Get the top element of the heap
    int top() {
        assert(!empty());
        return array[0];
    }

    // Check if the heap is empty
    bool empty() {
        return current_idx == -1;
    }

    // Check if the heap is full
    bool full() {
        return current_idx == (capacity - 1);
    }

    // Destructor
    ~maxHeap() {
        delete[] array;
        array = nullptr;
    }
};




/************************/
/* priority queue class */
/************************/
class priorityQueue{
private:
    maxHeap mx;
public:
    void push(int data) {
        mx.push(data);
    }

    int top() {
        return mx.top();
    }

    void pop() {
        mx.pop();
    }

    bool empty() {
        return mx.empty();
    }

    bool full(){
        return mx.full();
    }
};



/************************/
/*    heap sort class   */
/************************/
class heap_sort{
public:
    static void sort(int arr[], int n){
        maxHeap mx;

        for(int i=0; i<n; i++)
            mx.push(arr[i]);

        for(int i=n-1; i>=0; i--, mx.pop()){
            arr[i] = mx.top();
        }
    }
};


int main(){

    // Test the functions here
}