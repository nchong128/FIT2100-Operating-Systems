#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

int search(char *key, char *arr[], int arrLen);
int isPath(char *path);
void writeToFile(int infile, int outfile);
int invalidFlagsExist(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    int infile, outfile;
    char *dir = "./logfile.txt";
    char *filename = "logfile.txt";
    char *msg;
    char *targetdir;
    
    // PREPROCESSING: Check for invalid flags
    if (invalidFlagsExist(argc, argv) == 1) {
        msg = "fileutil: invalid option\n";
        write(2, msg, strlen(msg));
        exit(1);
    }

    // PREPROCESSING: CHECK FOR F, d and M FLAGS
    int fIndex = search("-F", argv, argc);
    int dIndex = search("-d", argv, argc);
    int mIndex = search("-M", argv, argc);

    // PREPROCESSING: Check if directory follows -d flag
    if (dIndex != -1) {
        if ((dIndex + 2 <= argc) && isPath(argv[dIndex+1]) == 0) {
            targetdir = argv[dIndex+1];
        } else {
            msg  = "fileutil: immediately after -d, a directory path was expected\n";
            write(2, msg, strlen(msg));
            exit(1);
        }
    } 
    
    // PREPROCESSING: DECIDE INFILE (EITHER argv[1] OR ./logfile.txt)
    // If file path specified, use argv[1]
    // If no file path specified, uses logfile.txt
    if (argc > 1 && isPath(argv[1]) == 0) {
        dir = argv[1];
    }

    filename = basename(strdup(dir));

    // Opens file unless error occurs
    if ((infile = open(dir, O_RDONLY)) < 0) {
        // close file
        msg = "fileutil: file could not be opened\n";
        write(2, msg, strlen(msg));
        exit(1);
    }

    // MAIN ACTIONS 
    if (dIndex != -1) {
        // -d present
        char* outpath = strcat(strcat(targetdir, "/"), filename);

        // open output file
        while ((outfile = open(outpath, O_WRONLY | O_CREAT | O_EXCL, 00700)) < 0) {
            if (fIndex != -1) {
                // if in force mode, unlink file
                msg = "fileutil: FORCE MODE ACTIVE\n";
                write(1, msg, strlen(msg));
                close(outfile);
                unlink(outpath);
            } else {
                // close files
                msg = "fileutil: destination directory already has a file with the same name as the source file OR directory does not exist\n";
                write(2, msg, strlen(msg));
                exit(2);
            }
        }

        writeToFile(infile, outfile);

        if (mIndex != -1) {
            unlink(dir);
            msg = "fileutil: move successful\n";
            write(1, msg, strlen(msg));
        } else {
            msg = "fileutil: copy successful\n";
            write(1, msg, strlen(msg));
        }
    } else if (mIndex == -1 && fIndex == -1) {
        // No arguments present 
        // PRINT FILE CONTENTS TO STDOUT
        writeToFile(infile, 1);        
    } else if (fIndex != -1) {
        // -F present only
        msg = "fileutil: invalid argument, -F is redundant as nothing to force here! \n";
        write(2, msg, strlen(msg));
        exit(1);
    } else {
        // -F OR -M present only
        msg = "fileutil: invalid argument, no destination to move the file! \n";
        write(2, msg, strlen(msg));
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

int invalidFlagsExist(int argc, char *argv[]) {
    int fCount, dCount, mCount;

    for (int i = 1; i < argc; i++) {
        if ((((isPath(argv[i]) == 0) && i != 1) && (strcmp("-d", argv[i-1]) != 0)) 
            && (strcmp("-d", argv[i]) != 0) 
            && (strcmp("-M", argv[i]) != 0) 
            && (strcmp("-F", argv[i]) != 0)) {
                return 1;
        }

        if (strcmp("-F", argv[i]) == 0) {
            fCount += 1;
        } else if (strcmp("-M", argv[i]) == 0) {
            mCount += 1;
        } else if (strcmp("-d", argv[i]) == 0) {
            dCount += 1;
        }

        if (fCount > 1 || dCount > 1 || mCount > 1) return 1;
    }

    return 0;
}