//
// Created by Mac on 27.02.2021.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class sorted_node {
private:
    float* array;
    int index;
    int size;
public:
    sorted_node(float* array, int index, int size): array(array), index(index), size(size) {}
    // No destructor - Not deleting the Node

    float current_value() {
        return array[index];
    }

    float operator*() {
        return array[index];
    }

    bool is_last() {
        return index + 1 == size;
    }

    sorted_node* next() {
        if(is_last()) throw "last node";

        return new sorted_node(array, index + 1, size);
    }

    void info() {
        cout << "Index: " << index << endl;
        cout << "Value: " << current_value() << endl;
        cout << "Last:" << is_last() << endl;
    }
};

class sorted_node_compare
{
public:
    bool operator() (sorted_node* n1, sorted_node* n2)
    {
        return n1->current_value() > n2->current_value();
    }
};

int merge_k_sorted(float** sorted_arrays, const int* array_sizes, int arrays_count, float*& output) {
    // Using Build-In priority queue to provide a custom comparator
    priority_queue<sorted_node*, vector<sorted_node*>, sorted_node_compare> sorted_heap;
    sorted_node* current_node;
    int output_size = 0, output_iter = 0;

    for(int i = 0; i < arrays_count; i++)
        output_size += array_sizes[i];

    output = new float[output_size];

    for(int i = 0; i < arrays_count; i++) {
        sorted_heap.push(new sorted_node(sorted_arrays[i], 0, array_sizes[i]));
    }

    while(!sorted_heap.empty()) {
        current_node = sorted_heap.top();
        sorted_heap.pop();

        current_node->info();

        output[output_iter++] = current_node->current_value();

        if(!current_node->is_last()) sorted_heap.push(current_node->next());

        delete current_node;
    }

    return output_size;
}
