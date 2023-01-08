/*
In the context of sorting, a heap is used as a particular way to sort elements. It is used by heapsort.

A heap can be considered a binary tree that is implemented as a sequential collection. Heaps have two properties:
1. The first element is always (one of) the largest.
2. You can add or remove an element in logarithmic time.

A heap is the ideal way to implement a priority queue: a queue that sorts its elements automatically so that the “next” element always is (one of) the largest. Therefore, the heap algorithms are used by the priority_queue container. The STL provides four algorithms to handle a heap:
1. make_heap() converts a range of elements into a heap.
2. push_heap() adds one element to the heap.
3. pop_heap() removes the next element from the heap.
4. sort_heap() converts the heap into a sorted collection, after which it is no longer a heap.

In addition, since C++11, is_heap() and is_heap_until() are provided to check whether a
collection is a heap or to return the first element that breaks the property of a collection to be a heap.
As usual, you can pass a binary predicate as the sorting criterion. The default sorting criterion is operator <.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class yHeap{
private:
    vector<T> heap;
    int leftChild(int i){
        return 2 * i + 1;
    }

    int rightChild(int i){
        return 2 * i + 2;
    }
    
    int parent(int i){
        return (i - 1) / 2;
    }

    void heapifyUp(int i){
        if(i < 1) return;
        int pi = parent(i);
        if(heap[pi] < heap[i]){
            swap(heap[pi], heap[i]);
            heapifyUp(pi);
        }
    }

    void heapifyDown(int i){
        int lc = leftChild(i);
        int rc = rightChild(i);
        int n = heap.size();
        int largest = i;
        if(lc < n && heap[largest] < heap[lc]){
            largest = lc;
        }
        if(rc < n && heap[largest] < heap[rc]){
            largest = rc;
        }
        if(largest != i){
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }
public:
    yHeap(vector<T>& data) : heap(data){
        makeHeap();
    }

    void makeHeap(){
        int n = heap.size();
        for(int i = n / 2; i >= 0; i--){
            heapifyDown(i);
        }
    }

    void pushHeap(T x){
        heap.push_back(x);
        heapifyUp(heap.size() - 1);
    }

    T popHeap(){
        swap(heap.front(),heap.back());
        T root = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return root;
    }

    vector<T> sortHeap(){
        vector<T> sorted;
        while(!heap.empty()){
            sorted.push_back(popHeap());
        }
        return sorted;
    }
    
    size_t size(){
        return heap.size();
    }
    vector<T> getHeap(){
        return heap;
    }
};

int main(){
    vector<int> data;
    int n = 100000;
    for(int i = 0; i < n; i++){
        data.push_back(rand());
    }
    yHeap<int> h(data);
    vector<int> sorted_data = h.sortHeap();
    sort(data.begin(),data.end(),greater<int>());
    int diff = 0;
    for(int i = 0; i < n; i++){
        if(sorted_data[i] != data[i]) diff++;
    }
    cout << diff <<endl;
}