#include <stdio.h>

int *find_smallest(int array[], int n);

int main(void) {
    int a[5] = {5,1,4,3,2};

    printf("The smallest number is %d\n", *find_smallest(a,5));
    return 0;
}

int *find_smallest(int array[], int n) {
    int *smallest = array;

    for (int i = 1; i < n; i++) {
        if (array[i] < *smallest) {
            smallest = &array[i];
        }
    } 
    return smallest;
}