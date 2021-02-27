//
// Created by Mac on 27.02.2021.
//

// TODO: Min / Max (Min for now)
// TODO: Switch between regular and opposite

#include "../heap.h"

float* subarray(int size, const float* array, int sub_size) {
    if(sub_size > size) throw "Sub-size cannot be larger than the original size";

    float* sub_array = new float[sub_size];

    for(int i = 0; i < sub_size; i++)
        sub_array[i] = array[i];

    return sub_array;
}

// Note: Let "size" be N in expression
// Finding Kth largest / smallest using an opposite Heap (Keeping a running subset of smallest)
float top_k_opposite(int size, const float* values, int k, bool smallest) {
    if(k > size) throw "K is greater than the size of the array";

    // Step 1. Heapifying the first K elements (From 0 to K-1 inclusively) -> O(K)
    heap<float> k_heap(k, subarray(size, values, k), !smallest); // Max-Subset of K SMALLEST (Going to be changed)
    // IMPORTANT: Using the opposite Heap-Direction (Smallest -> Max / Largest -> Min) - Just like with running median

    float current_value;

    // Step 2. For each element from K to N-1 -> (N-K)*LogK
    for(int i = k; i < size; i++) {
        current_value = values[i];

        // Check if it is less / greater than the current Subset-Top
        if(
            // Check if it is less than the current Subset-Top -> Changing the "Max-Subset of K SMALLEST"
                (smallest && current_value < k_heap.top()) ||
                // Check if it is larger than the current Subset-Top -> Changing the  "Min-Subset of K LARGEST"
                (!smallest && current_value > k_heap.top())
                ) {
            // Replacing the Subset-Top (Dropping previous one and heapifying for consistency -> New Subset-Top)
            k_heap.replace_top(current_value);
        }
    }

    // Step 3. Returning the largest element of "Max-Subset of K SMALLEST" / "Min-Subset of K LARGEST"
    //   -> LARGEST element of K SMALLEST is going to be the Kth SMALLEST from the ALL THE ITEMS (N)
    //   -> SMALLEST element of K LARGESTis going to be the Kth LARGEST from the ALL THE ITEMS (N)
    return k_heap.top();
}

// Note: Let "size" be N in expression
// Finding Kth largest / smallest using a Heap (Simply popping K-1 smallest / largest from the top) -> O(N + K * logN)
float top_k_regular(int size, const float* values, int k, bool is_smallest) {
    if(k > size) throw "K is greater than the size of the array";

    // Step 1. Heapifying ALL the elements -> O(N)
    heap<float> heap(size, values, is_smallest);

    // Step 2. Removing K-1 elements from the top -> O((K - 1) * logN) => O(K * logN)
    for(int i = 0; i < k - 1; i++) {
        heap.pop();
    }

    // Step 3. Returning the current top -> O(1)
    return heap.top();
}

// Note: Let "size" be N in expression
// Finding Kth largest / smallest using an opposite Heap (Keeping a running subset of smallest) -> O(K + (N-K) * logK)
float top_k(int size, const float* values, int k, bool smallest) {
    // Regular has better performance when asking for the Kth in the first half
    if (k < size / 2) {
        return top_k_regular(size, values, k, smallest);
    }

    // Opposite has better performance when asking for the Kth in the second half
    return top_k_opposite(size, values, k, smallest);
}
