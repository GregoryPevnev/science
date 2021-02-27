#include <iostream>
#include "heap.h"
#include "funcs/funcs.h"

using namespace std;

void test_min_heap_with_operations();

void test_min_heap_with_sorting();

void test_max_heap_with_operations();

void test_max_heap_with_sorting();

void test_running_median();

void test_top_k_subset();

void test_top_k();

void test_top_k_partitioned();

void test_merge_k_sorted();

int main() {
    srand((unsigned) time(nullptr));

    try {
        //    test_min_heap_with_operations();
        //    test_min_heap_with_sorting();
        //    test_max_heap_with_operations();
        //    test_max_heap_with_sorting();
//                test_running_median();
//        test_top_k_subset();
        //        test_top_k();
        //        test_top_k_partitioned();

        test_merge_k_sorted();

        return 0;
    } catch (char const* error) {
        cout << "Error: " << error << endl;
    }
}

void test_min_heap_with_operations() {
    const int size = 10;
    int values[] = {4, 1, 2, 5, 6, 3, 9, 8, 10, 7};
    heap<int> min_heap(size, true);

    for(int value : values)
        min_heap.add(value);

    cout << "Top: " << min_heap.top() << endl;

    for(int i = 0; i < size / 2; i++)
        cout << "Popped: " << min_heap.pop() << endl;

    min_heap.add(2);
    min_heap.add(19);
    min_heap.add(20);

    while(!min_heap.is_empty()) {
        cout << "Popped: " << min_heap.pop() << endl;
    }
}

void test_min_heap_with_sorting() {
    const int size = 10;
    int values[] = {4, 1, 2, 5, 6, 3, 9, 8, 10, 7};
    heap<int> min_heap(size, values, true);

    while(!min_heap.is_empty()) {
        cout << "Popped: " << min_heap.pop() << endl;
    }
}

void test_max_heap_with_operations() {
    const int size = 10;
    int values[] = {4, 1, 2, 5, 6, 3, 9, 8, 10, 7};
    heap<int> min_heap(size, false);

    for(int value : values)
        min_heap.add(value);

    cout << "Top: " << min_heap.top() << endl;

    for(int i = 0; i < size / 2; i++)
        cout << "Popped: " << min_heap.pop() << endl;

    min_heap.add(2);
    min_heap.add(19);
    min_heap.add(20);

    while(!min_heap.is_empty()) {
        cout << "Popped: " << min_heap.pop() << endl;
    }
}

void test_max_heap_with_sorting() {
    const int size = 10;
    int values[] = {4, 1, 2, 5, 6, 3, 9, 8, 10, 7};
    heap<int> min_heap(size, values, false);

    while(!min_heap.is_empty()) {
        cout << "Popped: " << min_heap.pop() << endl;
    }
}

void test_running_median() {
    const int size = 5;
    float values[] = {5, 15, 10, 20, 3};

    float* result = running_median(size, values);

    for(int i = 0; i < size; i++) {
        cout << result[i] << endl;
    }

    delete[] result;
}

void test_top_k_subset() {
    const int size = 5;
    const int k = 2;
    float values[] = {1, 2, 3, 4, 5};

    float* top_min_n = top_k_subset(size, values, k, true);
    float* top_max_n = top_k_subset(size, values, k, false);

    for(int i = 0; i < k; i++) {
        cout << "Top " << i + 1 << " min: " << top_min_n[i] << endl;
        cout << "Top " << i + 1 << " max: " << top_max_n[i] << endl;
    }

    delete[] top_min_n;
    delete[] top_max_n;
}

void test_top_k() {
    const int size = 6;
    float values[] = {7, 10, 4, 3, 20, 15};

    cout << "Top Kth smallest (" << 3 << "): " << top_k(size, values, 3, true) << endl;
    cout << "Top Kth smallest (" << 4 << "): " << top_k(size, values, 4, true) << endl;
    cout << "Top Kth largest (" << 3 << "): " << top_k(size, values, 3, false) << endl;
    cout << "Top Kth largest (" << 4 << "): " << top_k(size, values, 4, false) << endl;
}

void test_top_k_partitioned() {
    const int size = 6;
    float values[] = {7, 10, 4, 3, 20, 15};

    cout << "Top Kth smallest (" << 3 << "): " << top_k_partitioned(size, values, 3, true) << endl;
    cout << "Top Kth smallest (" << 4 << "): " << top_k_partitioned(size, values, 4, true) << endl;
    cout << "Top Kth largest (" << 3 << "): " << top_k_partitioned(size, values, 3, false) << endl;
    cout << "Top Kth largest (" << 4 << "): " << top_k_partitioned(size, values, 4, false) << endl;
}

void test_merge_k_sorted() {
    const int arrays_count = 3;

    int sizes[] = {3, 3, 2};

    float** arrays = new float*[arrays_count];
    arrays[0] = new float[]{2, 4, 6};
    arrays[1] = new float[]{1, 3, 5};
    arrays[2] = new float[]{0, 7};

    float* output; // Just to erase error

    int total = merge_k_sorted(static_cast<float **>(arrays), sizes, arrays_count, output);

    for(int i = 0; i < total; i++)
        cout << output[i] << endl;

    for(int i = 0; i < arrays_count; i++)
        delete[] arrays[i];

    delete[] arrays;
}
