#include <stdio.h>
#include <math.h>
int isPrime(int num);
int main() {
    int i = 101;
    
    while (i < 1000) {
        if (isPrime(i) == 1) {
            printf("The next prime after 100 is %d\n", i);
            return 0;
        }
        i++;
    }
    return 0;
}

int isPrime(int num) {
    for (int i = 2; i < sqrt(num); i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}