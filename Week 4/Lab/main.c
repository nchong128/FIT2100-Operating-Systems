#include <stdio.h>
#include "arithmetic.c"

int main(int argc, char *argv[]) {
    int a,b;

    printf("Enter first value:\n");
    scanf("%d", &a);
    printf("Enter second value:\n");
    scanf("%d", &b);

    printf("Sum: %d\n", add(a,b));
    printf("Difference: %d\n", subtract(a,b));
    printf("Product: %d\n", multiply(a,b));
    printf("Division: %.2f\n", divide(a,b));
}