//
// Created by Mac on 27.02.2021.
//

#include "../heap.h"

float* top_k_subset(int size, const float* values, int k, bool is_smallest) {
    if(k > size) throw "K is greater than the size of the array";

    float* result;
    heap<float> heap(size, values, is_smallest);

    result = new float[k];

    for(int i = 0; i < k; i++) {
        result[i] = heap.pop();
    }

    return result;
}
