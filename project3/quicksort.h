#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <string>
#include <vector>
#include "quicksort.h"

using namespace std;

void swap(string *a, string *b) {
    string temp = *a;
    *a = *b;
    *b = temp;
}

int partition(vector<string> &list, int left, int right, int pivot_idx) {
    int store_idx = left;
    int i = 0;
    string pivot_val = list[pivot_idx];
    // move the pivot to the end
    swap(&list[pivot_idx], &list[right]);
    // partition the current segment to L and R sections
    for (i = left; i < right; i++) {
    	if (list[i].compare(pivot_val) <= 0) {
            swap(&list[i], &list[store_idx]);
            store_idx++;
        }
    }
    // return the pivot to original position
    swap(&list[store_idx], &list[right]);
    return store_idx;
}

void quicksort(vector<string> &list, int left, int right) {
    // if the list does not have 2+ elements...we're done!
    if ( left < right) {
        // determine pivot
        int pivot_idx = left + (right - left) / 2;
        int new_idx = partition(list, left, right, pivot_idx);

        // recursively sort the L and R partitions
        quicksort(list, left, new_idx - 1);
        quicksort(list, new_idx + 1, right);
    }
}

#endif /* QUICKSORT_H */