//
// Created by Mac on 27.02.2021.
//

#ifndef SCIENCE_HEAP_H
#define SCIENCE_HEAP_H

// Important: Templates MUST be implemented in the same Header-File

// TODO: Add custom comparator???

template <typename T>
class heap {
private:
    T* items;
    int capacity;
    int size;
    bool is_min;

    bool compare(int, int);

    void swap(int, int);

    int find_next(int);

    void move_down(int);
    void move_up(int);

    void heapify();
public:
    explicit heap(int, bool); // Making sure multi-argument constructor is not used instead
    heap(int, const T*, bool);

    ~heap();

    bool is_empty();
    bool is_full();

    int current_size();

    void add(T);

    T pop();

    T top();

    void replace_top(T);
};

// IMPORTANT: ANY VALUE EXCEPT 0 is TRUE in C++
template <class T>
bool heap<T>::compare(int index1, int index2) {
    // V1 is less than V2
    if(is_min) return items[index2] > items[index1];

    // V1 is greater than V2
    return items[index1] > items[index2];
}

template <class T>
void heap<T>::swap(int from_index, int to_index) {
    T tmp = items[from_index];
    items[from_index] = items[to_index];
    items[to_index] = tmp;
}

template <class T>
int heap<T>::find_next(int index) {
    int left = index * 2;
    int right = index * 2 + 1;

    if(left > size) return index;

    if(right > size) return left;

    return compare(left, right) ? left : right;
}

template <class T>
void heap<T>::move_up(int index) {
    if(index == 1) return;

    int parent = index / 2; // Note: Flooring by default (No matter how large)

    if(compare(index, parent)) {
        swap(parent, index);
        move_up(parent);
    }
}

template <class T>
void heap<T>::move_down(int index) {
    int next = find_next(index);

    if(index == next) return;

    if (compare(next, index)) {
        swap(next, index);
        move_down(next);
    }
}

template <class T>
void heap<T>::heapify() {
    int middle = size / 2;

    for(int i = middle; i > 0; i--) {
        move_down(i);
    }
}

template <class T>
heap<T>::heap(int capacity, bool is_min) : capacity(capacity), size(0), is_min(is_min) {
    this->items = new T[capacity + 1];
    this->items[0] = 0;
}

template <class T>
heap<T>::heap(int capacity, const T *values, bool is_min) : capacity(capacity), size(capacity), is_min(is_min) {
    this->items = new T[capacity + 1];
    this->items[0] = 0;

    for(int i = 0; i < capacity; i++) {
        this->items[i + 1] = values[i];
    }

    heapify();
}

template <class T>
heap<T>::~heap() {
    delete[] items;
}

template <class T>
bool heap<T>::is_empty() {
    return size == 0;
}

template <class T>
bool heap<T>::is_full() {
    return size == capacity;
}

template <class T>
int heap<T>::current_size() {
    return size;
}

template <class T>
void heap<T>::add(T value) {
    if(is_full()) throw "heap is full";

    items[++size] = value;

    move_up(size);
}

template <class T>
T heap<T>::pop() {
    if(is_empty()) throw "heap is empty";

    swap(1, size--);

    move_down(1);

    return items[size + 1];
}

template <class T>
T heap<T>::top() {
    if(is_empty()) throw "heap is empty";

    return items[1];
}

template <class T>
void heap<T>::replace_top(T new_top) {
    items[1] = new_top;

    move_down(1);
}

#endif //SCIENCE_HEAP_H
