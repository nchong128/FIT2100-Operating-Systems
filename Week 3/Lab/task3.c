#include <stdio.h>

int main(void) {
    int a,b;
    int rem, quo;

    printf("Enter first integer\n");
    scanf("%d", &a);
    printf("Enter second integer\n");
    scanf("%d", &b);
    rem = a % b;
    quo = a / b;

    while (rem != 0) {
        a = b;
        b = rem;
        quo = a / b;
        rem = a - (b * quo);
    }
    printf("GCD is %d\n", b);
}