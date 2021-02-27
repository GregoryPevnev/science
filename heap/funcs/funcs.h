//
// Created by Mac on 27.02.2021.
//

#ifndef SCIENCE_FUNCS_H
#define SCIENCE_FUNCS_H

// Note: Returning subset (DB implementation)
float* top_k_subset(int, const float*, int, bool);

// Note: Returning a single element
float top_k(int, const float*, int, bool);

// Note: Using QuickSelect and Partitioning
float top_k_partitioned(int, const float*, int, bool);

float* running_median(int, const float*);

int merge_k_sorted(float**, const int*, int, float*&);

#endif //SCIENCE_FUNCS_H
