#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *first_name;
    char *last_name;
} Name;

typedef enum {false, true} bool;

bool compareNames(Name name1, Name name2);

int main(void) {
    Name me, you;

    me.first_name = "Nick";
    me.last_name = "Chong";

    you.first_name = "Nik";
    you.last_name = "Chong";

    if (compareNames(me, you) == true) {
        printf("Names are the same\n");
    } else {
        printf("Names are not the same\n");
    }

}

bool compareNames(Name name1, Name name2) {
    return
        (strcmp(name1.first_name, name2.first_name) == 0 && strcmp(name1.last_name, name2.last_name) == 0)
    ? true : false;
}