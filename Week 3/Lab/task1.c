#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;

int main(void) {
    int hh,mm;
    bool isAM = true;

    printf("Enter hours \n");
    scanf("%d\n", &hh);
    printf("Enter minutes \n");
    scanf("%d\n", &mm);

    // convert hours
    if (hh > 12) {
        isAM = false;
        hh = hh - 12;
    } else if (hh == 0) {
        hh = 12;
    }

    printf("%d:%d %s", hh, mm, isAM ? "am" : "pm");








}