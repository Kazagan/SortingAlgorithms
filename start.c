#include <stdio.h>
#include <stdlib.h>

void assert_array(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*));
int int_equality(const void * first, const void * second);

int main() {
    
    // Initialize some arrays of differing types.

    int unordered_int[10] = { 20, 30, 5, 9, 60, 55, 2, 9, 89, 38 };
    int ordered_int[10] = { 2, 5, 9, 9, 20, 30, 38, 55, 60, 89 };
    // This is where I would call my sorting Algorithm... IF I HAD ONE!!
    
    // Assert equals.
    assert_array(sizeof(int), ordered_int, 10, unordered_int, 10, int_equality);
    
    return 0;
}

int int_equality(const void * expected, const void * actual) {
    if(*(int*)expected != *(int*)actual) {
        fprintf(stderr, "Error: expected valued %d, differend with actual %d\n", *(int*)expected, *(int*)actual);
        return 0;
    }
    return 1;
}

void assert_array(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*)) {
    if(expected_size != actual_size) {
        fprintf(stderr, "Error: actual size %ld does not equal expected size %ld\n", actual_size, expected_size);
        exit(-1);
    }
    for(int i = 0; i < expected_size; i++) {
        if(comparison(expected, actual) != 1) {
            fprintf(stderr, "arrays differ at element %d\n", i+1);
            exit(-1);
        }
        expected += type_size;
        actual += type_size;
    }
}
