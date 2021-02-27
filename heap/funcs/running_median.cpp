//
// Created by Mac on 27.02.2021.
//

#include "../heap.h"

float* running_median(int size, const float* values) {
    float *medians;

    if(size == 0) return new float[0];

    const int heap_size = size / 2 + 1; // One extra spot when the heaps need to be rebalanced

    heap<float> lesser_values(heap_size, false);
    heap<float> greater_values(heap_size, true);

    float current_number;
    float current_value = values[0];

    int balance = 0;

    medians = new float[size];
    medians[0] = current_value;

    // Starting from 2 to have correct ODD / EVEN counter
    for(int i = 2; i < size + 1; i++) {
        current_number = values[i - 1];

        // Adding new value
        if(current_number >= current_value) {
            // Adding to the greater ones
            greater_values.add(current_number);
        } else {
            // Adding to the lesser ones
            lesser_values.add(current_number);
        }

        // Recomputing balance
        balance = lesser_values.current_size() - greater_values.current_size();

        // Balancing
        if(balance >= 2) {
            // More lesser elements
            greater_values.add(current_value);
            current_value = lesser_values.pop();
        } else if (balance <= -2) {
            // More greater elements
            lesser_values.add(current_value);
            current_value = greater_values.pop();
        }

        // ODD Case
        if(i % 2 == 1) {
            medians[i - 1] = current_value;

            continue;
        }

        // EVEN Case
        // Balance CANNOT be 0 when EVEN
        if(balance > 0) {
            // More lesser elements
            medians[i - 1] = (lesser_values.top() + current_value) / 2;
        } else {
            // More greater elements
            medians[i - 1] = (greater_values.top() + current_value) / 2;
        }
    }

    return medians;
}
