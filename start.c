#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

int assert_array(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*));
int assert_array_not(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*));
int int_comp(const void * first, const void * second);
int str_comp(const void * first,const void * second);
int dbl_comp(const void * first, const void * second);

int test_int() {
    int unordered_int[10] = { 20, 30, 5, 9, 60, 55, 2, 9, 89, 38 };
    int ordered_int[10] = { 2, 5, 9, 9, 20, 30, 38, 55, 60, 89 };   
    
    /* assert_array_not(sizeof(int), ordered_int, 10, unordered_int, 10, int_comp); */
    for(int i = 0; i < 10; i++) printf("%d|%d,  ", unordered_int[i], ordered_int[i]); 
    printf("\n");
    
    my_sort(unordered_int, 10, sizeof(int), int_comp);
    
    for(int i = 0; i < 10; i++) printf("%d|%d,  ", unordered_int[i], ordered_int[i]); 
    printf("\n");
    
    assert_array(sizeof(int), ordered_int, 10, unordered_int, 10, int_comp);
    return 0;
}

int test_str() {
    char *unordered_str[10] = { "MARY", "PATRICIA", "LINDA", "BARBARA", "ELIZABETH", "JENNIFER", "MARIA", "SUSAN", "MARGARET", "DOROTHY" };
    char *ordered_str[10] = { "BARBARA", "DOROTHY", "ELIZABETH", "JENNIFER", "LINDA", "MARGARET", "MARIA", "MARY", "PATRICIA", "SUSAN" };
    assert_array_not(sizeof(const char*), ordered_str, 10, unordered_str, 10, str_comp);
    my_sort(unordered_str, 10, sizeof(const char*), str_comp);
    assert_array(sizeof(const char*), ordered_str, 10, unordered_str, 10, str_comp);   
    
    for(int i = 0; i < 10; i++) printf("%s|%s,  ", unordered_str[i], ordered_str[i]); 
    printf("\n");
    return 0;
}

int test_dbl() {
    double unordered_dbl[10] = { 2.533246255434451, 4.304745182255861, 4.691286445313874, 4.945368896029029, 0.4553754510705249, 4.308538646842419, 0.20165444744552619, 3.23184655888265, 1.1330869559589551, 1.1371835761393312 };
    double ordered_dbl[10] =  { 0.20165444744552619, 0.4553754510705249, 1.1330869559589551, 1.1371835761393312, 2.533246255434451, 3.23184655888265, 4.304745182255861, 4.308538646842419, 4.691286445313874, 4.945368896029029 };
    assert_array_not(sizeof(double), ordered_dbl, 10, unordered_dbl, 10, dbl_comp);
    my_sort(unordered_dbl, 10, sizeof(double), dbl_comp);
    assert_array(sizeof(double), ordered_dbl, 10, unordered_dbl, 10, dbl_comp);   
    
    for(int i = 0; i < 10; i++) printf("%f|%f,  ", unordered_dbl[i], ordered_dbl[i]); 
    printf("\n");
    return 0;
}

int main() {
    test_int();
    test_str();
    test_dbl();
}

int int_comp(const void * first, const void * second) {
    /* printf("first: %d, Second: %d\n", *(int*)first, *(int*)second); */
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

int dbl_comp(const void * first, const void * second) {
    double result = *(double*)first - *(double*)second;
    if(result > 0) return 1;
    if(result < 0) return -1;
    return 0;
}

int assert_array(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*)) {
    if(expected_size != actual_size) {
        fprintf(stderr, "Error: actual size %ld does not equal expected size %ld\n", actual_size, expected_size);
        exit(-1);
    }
    for(int i = 0; i < expected_size; i++) {
        if(comparison(expected, actual) != 0) {
            fprintf(stderr, "arrays differ at element %d\n", i+1);
            exit(-1);
        }

        expected += type_size;
        actual += type_size;
    }
    return 1;
}

int assert_array_not(size_t type_size, void *expected, size_t expected_size, void *actual, size_t actual_size, int (*comparison)(const void *, const void*)) {
    if(expected_size != actual_size) {
        return 1;
    }
    int compare = 0;
    for(int i = 0; i < expected_size; i++) {
        compare += comparison(expected, actual);
        if(comparison(expected, actual) != 0) {
            return 1;
        }        
        expected += type_size;
        actual += type_size;
    }
    if(compare == 0) {
        printf("Arrays are not different");
        exit(-1);
    }
    return 0;
}
