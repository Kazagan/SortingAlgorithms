#include <stdio.h>

void swap(void * first, void * second, size_t element_size)
{
    unsigned char * f = first, * s = second, tmp;
    for (size_t i = 0; i != element_size; ++i)
    {
        tmp = f[i];
        f[i] = s[i];
        s[i] = tmp;
    }
}


//Step one, qSort
/* void my_sort(void *arry, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) { */
/*     qsort(arry, element_count, element_size, comparer); */
/* } */

// First Custom, Bubble sort

void bubble_sort(void *arry, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) {
    int is_sorted = 0;
    void *start = arry;
    while(is_sorted != 1) {
        is_sorted = 1;
        arry += element_size;
        for(int i = 1; i < element_count; i++) {
            if(comparer(arry - element_size, arry) > 0) {
                is_sorted = 0;
                swap(arry - element_size, arry, element_size);
            }
            arry += element_size;
        }
        arry = start;
    }
}

void my_sort(void *arry, size_t element_count, size_t element_size, int (*comparer)(const void *, const void *)) { 
    for(int i = 0; i < element_count; i++) {
        void *smallest = arry + (element_size * i);
        for(int j = i+1; j < element_count; j++) {
            void *check = arry + (element_size * j);
            if(comparer(smallest, check) > 0) {
                smallest = check;
            }
        }
        swap(arry + (element_size * i), smallest, element_size);
    }
}
