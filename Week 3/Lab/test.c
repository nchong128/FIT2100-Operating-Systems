#include <stdio.h>

int main(void) {
    char str1[] = "FIT2100 Operating Systems";
    char str2[] = "Week 3 Tutorial";
    char str3[] = "ABCDEF";
    char *ptr = NULL;

    ptr = str1;
    printf("%s\n", ptr);

    ptr = str2;
    printf("%s\n", *ptr);

    return 0;
}