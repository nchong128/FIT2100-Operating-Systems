#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int n, infile, outfile;
    ssize_t inbytes, outbytes;
    size_t nbytes = 1024;
    char buffer[nbytes];

    if (argc != 3) {
        write(2, "Usage: ./appendfile file1 file2\n", 32);
        exit(1);
    }

    if ((infile = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(1);
    }

    if ((outfile = open(argv[2], O_WRONLY | O_APPEND)) < 0) {
        perror(argv[2]);
        exit(1);
    }

    /*
     * Copy contents of first file to second file
     */
    while ((inbytes = read(infile, buffer, nbytes)) != 0) {
        outbytes = write(outfile, buffer, inbytes);

        if (outbytes == 0) {
            break;
        }
    }
    
    close(infile);
    close(outfile);
    exit(0);
}