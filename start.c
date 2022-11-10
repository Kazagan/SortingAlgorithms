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
    int a = 5;
    int b = 7;
    int x = int_equality(&a, &b);
    printf("%d\n", x);
    
    return 0;
}

int int_equality(const void * first, const void * second) {
    if(*(int*)first != *(int*)second) {
        return 0;
    }
    return 1;
}

void assert_array(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*)) {
    if(expected_size != actual_size) {
        fprintf(stderr, "actual size %ld does not equal expected size %ld", expected_size, actual_size);
        exit(-1);
    }
    for(int i = 0; i < expected_size; i++) {
        if(comparison(expected[i], actual[i]) != 1) {
            fprintf(stderr, "arrays differ at %d\n", i);
            exit(-1);
        }
    }
}
