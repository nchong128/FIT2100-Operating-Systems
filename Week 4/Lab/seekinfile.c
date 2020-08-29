/**
 * Program opens a file named 'recordfile' and loops over the various users.
 * It uses lseek to offset from the beginning of the file TO the given position based on the index.
 * It uses write to dump the contents of the current record into a binary file.
 * In this program, it uses the struct as a buffer to write the contents in.
 */ 

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct record {
    int userid;
    char username[6];
};

char *usernames[] = { "userA", "userB", "userC", "userD" };

int main(int argc, char *argv[]) {
    int i, outfile, len, infile;
    struct record eachrec;
    char *curruser, *msg;
    int indices[] = { 1,3,0,2 };

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

    msg = "Reading in files\n";
    write(1, msg, strlen(msg));
    
    // open recordfile to read only
    infile = open("recordfile", O_RDONLY);
    len = sizeof(indices) / sizeof(int);

    // loop over indices in special order
    for (int i = 0; i < len; i++) {
        // point lseek to position based on index and read to struct var
        lseek(infile, (long) indices[i] * sizeof(struct record), SEEK_SET);
        read(infile, &eachrec, sizeof(struct record));

        // grab username from struct var and write to std output
        curruser = eachrec.username;
        write(1, curruser, strlen(curruser));
        write(1, "\n", 1);
    }

    close(outfile);
    exit(0);
}