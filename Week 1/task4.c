#include <stdio.h>

int main(int argc, char *argv[]) {
    int num;
    int reversed[3];

    printf("Enter number:\n");
    scanf("%d", &num);

    // put num into reversed
    for (int i = 0; i < 3; i++) {
        reversed[i] = num % 10;
        num = num / 10;
    }

    // print reversed
    for (int i = 0; i < 3; i++ ) {
        printf("%d", reversed[i]);
    }
    printf("\n");

    return 0;
}