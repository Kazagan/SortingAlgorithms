#include <stdio.h>
#include <stdlib.h>

void assert_array(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*));
int int_comp(const void * first, const void * second);
int str_comp(const void * first,const void * second);

int main() {
    
    // Initialize some arrays of differing types.
    int unordered_int[10] = { 20, 30, 5, 9, 60, 55, 2, 9, 89, 38 };
    int ordered_int[10] = { 2, 5, 9, 9, 20, 30, 38, 55, 60, 89 };
    int test_int[10] = { 2, 5, 9, 9, 20, 30, 38, 55, 60, 89 };
    
    char *unordered_str[10] = { "MARY", "PATRICIA", "LINDA", "BARBARA", "ELIZABETH", "JENNIFER", "MARIA", "SUSAN", "MARGARET", "DOROTHY" };
    char *ordered_str[10] = { "BARBARA", "DOROTHY", "ELIZABETH", "JENNIFER", "LINDA", "MARGARET", "MARIA", "MARY", "PATRICIA", "SUSAN" };
    char *test_str[10] = { "BARBARA", "DOROTHY", "ELIZABETH", "JENNIFER", "LINDA", "MARGARET", "MARIA", "MARY", "PATRICIA", "SUSAN" };
    
    // Lets use QSort to tests my compareres for now.
    qsort(unordered_int, 10, sizeof(int), int_comp);
    qsort(unordered_str, 10, sizeof(const char*), str_comp);
    // This is where I would call my sorting Algorithm... IF I HAD ONE!!
    
    // Assert equals.

    assert_array(sizeof(int), ordered_int, 10, test_int, 10, int_comp);
    assert_array(sizeof(const char*), ordered_str, 10, test_str, 10, str_comp);
    
    assert_array(sizeof(int), ordered_int, 10, unordered_int, 10, int_comp);
    assert_array(sizeof(const char*), ordered_str, 10, unordered_str, 10, str_comp);
}

int int_comp(const void * first, const void * second) {
    return *(int*)first - *(int*)second;
}

int str_comp(const void * first,const void * second) {
    int i = 0;
    int result = 0;
    char* x = *(char**)first;
    char* y = *(char**)second;
    while(x[i] != '\0') {
        result = x[i] - y[i];
        i++;
        if(result != 0) return result;
    }
    return 0;
}

void assert_array(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*)) {
    if(expected_size != actual_size) {
        fprintf(stderr, "Error: actual size %ld does not equal expected size %ld\n", actual_size, expected_size);
        /* exit(-1); */
    }
    for(int i = 0; i < expected_size; i++) {
        if(comparison(expected, actual) != 0) {
            fprintf(stderr, "arrays differ at element %d\n", i+1);
            /* exit(-1); */
        }

        expected += type_size;
        actual += type_size;
    }
}
