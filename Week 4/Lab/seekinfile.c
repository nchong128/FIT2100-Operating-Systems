#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct record {
    int userid;
    char username[6];
}

char *usernames[] = { "userA", "userB", "userC", "userD" };

int main(int argc, char *argv[]) {
    int i, outfile;
    struct record eachrec;

    if ((outfile = open("recordfile", O_WRONLY | O_CREAT, 0664)) < 0) {
        perror("recordfile");
        exit(1);
    }

    for (i = 3; i >= 0; i-- ) {
        eachrec.userid = i;
        strcpy(eachrec.username, usernames[i]);

        lseek(outfile, (long) i * sizeof(struct record), SEEK_SET);
        write(outfile, &eachrec, sizeof(struct record));
    }


    close(outfile);
    exit(0);



}