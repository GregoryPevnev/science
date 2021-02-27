//
// Created by Mac on 27.02.2021.
//

// TODO: Move to Quick-Sort when implemented

#include <cstdlib>

void swap(float* array, int i, int j) {
    float tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

// Performing regular quick-sort partition
int partition(float* values, int start, int end) {
    // Single element -> Skip
    // if(start == end) return start;
    //   - Already checked in main-function

    float pivot = values[end];
    int i = start, j = end - 1;

    while(i <= j) {
        while(i <= j && values[i] <= pivot) i++;

        while(i <= j && values[j] >= pivot) j--;

        if(i <= j) {
            swap(values, i++, j--);
        }
    }

    swap(values, i, end);

    return i;
}

int partition_with_random_pivot(float* values, int start, int end) {
    // No invalid random number
    // if(start == end) return start;
    //   - Already checked in main-function

    // Getting random item to be the pivot
    int random_pivot = (rand() % (end - start)) + start;

    // Swapping it with the last-value (Going to be used as a pivot) - Could instead be the first one
    swap(values, random_pivot, end);

    return partition(values, start, end);
}

// Finding Kth smallest element - Simply subtracting from the total size when searching for the largest
float find_kth_smallest(float* values, int start, int end, int k) {
    if(start == end) return values[start];

    // Getting Partition-Index (Place of Pivot / Found location of an element)
    int partition_index = partition_with_random_pivot(values, start, end);
    // Important: Using Random-Pivot to avoid Worst-Case - Could just shuffle instead

    // Less than Kth position -> Search the upper half
    if(partition_index < k - 1) return find_kth_smallest(values, partition_index + 1, end, k);

    // Greater than Kth position -> Search the lower half
    if(partition_index > k - 1) return find_kth_smallest(values, start, partition_index - 1, k);

    // Exactly the same as Kth position -> Kth smallest found
    return values[partition_index];
}

// Using Partitioning of QuickSort to find an appropriate Pivot that corresponds to the Kth Largest / Smallest
//   -> O(n) when randomized (Complex proof similar to Heap-Sort)
float top_k_partitioned(int size, const float* values, int k, bool is_smallest) {
    float* mutable_values = new float[size];

    for(int i = 0; i < size; i++)
        mutable_values[i] = values[i];

    // Searching for the opposite when searching for the largest K
    //   - Adding 1 for taking the element's position into account (6 - 3 = 3 + 1 = 4) -> {1,2,3,[4],5,6} - 3rd Largest
    int search_k = is_smallest ? k : (size - k + 1);

    float result = find_kth_smallest(mutable_values, 0, size - 1, search_k);

    delete[] mutable_values;

    return result;
}
