#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>

int search(char *key, char *arr[], int arrLen);
int isPath(char *path);
void writeToFile(int infile, int outfile);

int main(int argc, char *argv[]) {
    int infile, outfile;
    char *dir = "./logfile.txt";
    char *msg;
    char *filename = "logfile.txt";
    char *targetdir;

    // PREPROCESSING: CHECK FOR F, d and M FLAGS
    int fIndex = search("-F", argv, argc);
    int dIndex = search("-d", argv, argc);
    int mIndex = search("-M", argv, argc);

    printf("argc:%d\n", argc);
    printf("d:%d ,M:%d , F:%d\n", dIndex, mIndex, fIndex);

    // PREPROCESSING: Check if directory follows -d flag
    if (dIndex != -1 && (dIndex + 2 <= argc) && isPath(argv[dIndex+1]) == 0) {
        targetdir = argv[dIndex+1];
    }
    
    // PREPROCESSING: DECIDE INFILE (EITHER argv[1] OR ./logfile.txt)
    // If file path specified, use argv[1]
    // If no file path specified, uses logfile.txt
    if (argc > 1 && isPath(argv[1]) == 0) {
        dir = argv[1];
    }

    filename = basename(strdup(dir));
    printf("File name: %s\n", filename);

    // Opens file unless error occurs
    if ((infile = open(dir, O_RDONLY)) < 0) {
        // close file
        perror("File could not be opened");
        exit(1);
    }

    // MAIN ACTIONS 
    if (dIndex != -1) {
        // -d present
        char* outpath = strcat(strcat(targetdir, "/"), filename);

        // make output file
        while ((outfile = open(outpath, O_WRONLY | O_CREAT | O_EXCL, 0664)) < 0) {
            if (fIndex != -1) {
                // if in force mode, unlink file
                close(outfile);
                unlink(outpath);
            } else {
                // close files
                perror("Destination directory already has a file with the same name as the source file OR directory does not exist");
                exit(2);
            }
        }

        writeToFile(infile, outfile);

        if (mIndex != -1) {
            unlink(dir);
            msg = "Move successful\n";
            write(1, msg, strlen(msg));
        } else {
            msg = "Copy successful\n";
            write(1, msg, strlen(msg));
        }

    } else if (mIndex == -1 && fIndex == -1) {
        // No arguments present 
        // PRINT FILE CONTENTS TO STDOUT
        writeToFile(infile, 1);        
    } else if (fIndex != -1) {
        // -F present only
        perror("Invalid argument, -F is redundant as nothing to force here!");
        exit(1);
    } else {
        // -F OR -M present only
        perror("Invalid argument, no destination to move the file!");
        exit(1);
    }

    close(infile);
    close(outfile);
    exit(0);
}

void writeToFile(int infile, int outfile) {
    ssize_t inbytes, outbytes;
    size_t nbytes = 1024;
    char buffer[nbytes];

    lseek(infile, 0, SEEK_SET);
    while ((inbytes = read(infile, buffer, nbytes)) != 0) {
        outbytes = write(outfile, buffer, inbytes);

        if (outbytes == 0) break;
    }
}

int search(char *key, char *arr[], int arrLen) {
    // Returns first located index of key
    // If not in arr, returns -1
    for (int i = 0; i < arrLen; i++) {
        if (strcmp(key, arr[i]) == 0 ) {
            return i;
        }
    } 
    return -1;
}

int isPath(char *path) {
    char firstChar = path[0];
    return strcmp(&firstChar, "/");
}