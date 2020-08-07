#include <stdio.h>

int main(int argc, char *argv[]) {
    char firstName[20], lastName[20];
    printf("Your first name is:\n");
    scanf("%s", firstName);
    printf("Your last name is:\n");
    scanf("%s", lastName);
    printf("Your initials are %c%c\n", firstName[0], lastName[0]);
    return 0;
}