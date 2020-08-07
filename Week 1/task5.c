#include <stdio.h>
#include <stdlib.h>
#include<time.h> 

int main(int argc, char *argv[]) {
    srand(time(0));

    for (int i = 0; i < 6; i ++) {
        printf("%d",rand() % 10);
    }
    printf("\n");


    return 0;
}