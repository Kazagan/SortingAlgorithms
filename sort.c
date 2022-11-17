#include <stdio.h>
#include <stdlib.h>

// This locks me in as using element_size to always represent the data size of the array elements, but hopefully will make it more readable and easier to work with.
#define POINTER_INDEX(x) + (x * element_size)

void swap(void * first, void * second, size_t data_size)
{
    unsigned char * f = first, * s = second, tmp;
    for (size_t i = 0; i < data_size; i++) {
        tmp = f[i];
        f[i] = s[i];
        s[i] = tmp;
    }
}

void copy(void *target, void *source, size_t data_size) {
    unsigned char * t = target, * s = source;
    for (size_t i = 0; i < data_size; i++) {
        t[i] = s[i];
    }
}

void q_sort(void *sort_array, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    qsort(sort_array, element_count, element_size, comparer);
}

// First Custom, Bubble sort

void bubble_sort(void *sort_array, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    int is_sorted = 0;
    void *start = sort_array;
    while(is_sorted != 1) {
        is_sorted = 1;
        sort_array += element_size;
        for(int i = 1; i < element_count; i++) {
            if(comparer(sort_array - element_size, sort_array) > 0) {
                is_sorted = 0;
                swap(sort_array - element_size, sort_array, element_size);
            }
            sort_array += element_size;
        }
        sort_array = start;
    }
}

void selection_sort(void *sort_array, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    for(int i = 0; i < element_count - 1; i++) {
        void *smallest = sort_array POINTER_INDEX(i);
        for(int j = i+1; j < element_count; j++) {
            void *check = sort_array + (element_size * j);
            if(comparer(smallest, check) > 0) {
                smallest = check;
            }
        }
        swap(sort_array POINTER_INDEX(i), smallest, element_size);
    }
}

void insertion_sort(void *sort_array, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    for(int i = 1; i < element_count; i++) {
        void *current = sort_array POINTER_INDEX(i);
        int j = i - 1;
        void *check = sort_array POINTER_INDEX(j);
        while(comparer(check, current) > 0) {
            swap(current, check, element_size);
            current = sort_array POINTER_INDEX(j); // set pointer for current to its new location
            if(j == 0) break; // Avoid going out of array bounds
            check = sort_array POINTER_INDEX(--j); // set next check
        }
    }
}

void merge(void *sort_array, size_t element_size, size_t left, size_t middle, size_t right, int (*comparer)(const void *, const void *)) {
    // Get sizes
    size_t size_left = middle - left + 1;
    size_t size_right = right - middle;

    // initialize split arrays
    void *left_array = malloc(element_size * size_left);
    void *right_array = malloc(element_size * size_right);

    //copy into split arrays
    for(int i = 0; i < size_left; i++) {
        int index = left + i;
        copy(left_array POINTER_INDEX(i), sort_array POINTER_INDEX(index), element_size);
    }
    for(int i = 0; i < size_right; i++) {
        int index = middle + 1 + i;
        copy(right_array POINTER_INDEX(i), sort_array POINTER_INDEX(index), element_size);
    }
    
    // start copying back
    size_t left_index = 0;
    size_t right_index = 0;
    size_t original_left = left;
    while(left_index < size_left && right_index < size_right) {
        void *x = left_array POINTER_INDEX(left_index);
        void *y = right_array POINTER_INDEX(right_index);
        if(comparer(x, y) <= 0) { // x <= y
            copy( sort_array POINTER_INDEX(original_left), x, element_size);
            left_index++;
        } else {
            copy( sort_array POINTER_INDEX(original_left), y, element_size);
            right_index++;
        }
        original_left++;
    }

    //copy left over in uneven arrays
    while(left_index < size_left) {
        copy(sort_array POINTER_INDEX(original_left++), left_array + POINTER_INDEX(left_index++), element_size);
    }
    while(right_index < size_right) {
        copy(sort_array POINTER_INDEX(original_left++), right_array + POINTER_INDEX(right_index++), element_size);
    }
}

void mergeSort(void *sort_array, size_t element_size, size_t left_index, size_t right_index, int (*comparer)(const void *, const void *)) {
    if( left_index >= right_index ) return;
    size_t middle  = left_index + ( right_index - left_index ) / 2;

    mergeSort(sort_array, element_size, left_index, middle, comparer);
    mergeSort(sort_array, element_size, middle+1, right_index, comparer);

    merge(sort_array, element_size, left_index, middle, right_index, comparer);
}

void merge_sort(void *sort_array, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    mergeSort(sort_array, element_size, 0, element_count - 1, comparer);
}

int partition(void *sort_array, size_t element_size, int left, int right, int (*comparer)(const void *, const void *)) {
    void *pivot = sort_array POINTER_INDEX(right);
    int i = left;
    for(int current = left; current < right; current++) {
        if(comparer( pivot, sort_array POINTER_INDEX(current) ) > 0 ) {
            swap( sort_array POINTER_INDEX(i++), sort_array POINTER_INDEX(current), element_size); 
        }
    }
    swap(pivot, sort_array POINTER_INDEX(i), element_size);
    return i;
}

void quickSort(void *sort_array, size_t element_size, int left, int right, int (*comparer)(const void *, const void *)) {
    if(left >= right) return;
    int partition_index = partition(sort_array, element_size, left, right, comparer);
    quickSort(sort_array, element_size, left, partition_index - 1, comparer);
    quickSort(sort_array, element_size, partition_index + 1, right, comparer);
}    

void quick_sort(void *sort_array, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    int left = 0;
    int right = element_count - 1;
    quickSort(sort_array, element_size, left, right, comparer);
}

void my_sort(void *sort_array, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    quick_sort(sort_array, element_count, element_size, comparer);
}
