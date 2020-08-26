#include <stdio.h>

int main() {
    char string[1234];

    printf("Enter a word: ");
    scanf("%s", string);

    printf("You entered: %s", string);

    return 0;
}
