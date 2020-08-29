#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print(char *msg);

int main(int argc, char *argv[]) {
    int infile;
    ssize_t inbytes, outbytes;
    size_t nbytes = 1024;
    char buffer[nbytes], *filename;

    // If no file path specified, uses logfile.txt
    filename = (strcmp(&argv[1][0], "/") == 0) ? "README.txt" : "logfile.txt";
    // filename = "logfile.txt";


    // Opens file
    if ((infile = open(filename, O_RDONLY)) < 0) {
        perror("Logfile could not be opened.");
        exit(1);
    }

    // Loop over file and print outputs
    while ((inbytes = read(infile, buffer, nbytes)) != 0) {
        outbytes = write(1, buffer, inbytes);

        if (outbytes == 0) {
            break;
        }
    }

    close(infile);
    exit(0);
}

// TODO: Remove
void print(char *msg) {
    write(1, msg, strlen(msg));
}