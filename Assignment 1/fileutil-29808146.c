/**
 * File name: fileutil-29808146.c
 * Author name: Nicholas Lin Ren Chong
 * Student ID: 29808146
 * Start date: 1 September 2020
 * Last modified date: 11 September 2020
 * Description: 
 * This source file contains the code required for the fileutil utility module,
 * created for Assignment 1 of FIT2100, S2 2020.The functionality provided includes
 * copying, moving and printing of text files, similar to cp, mv and cat respectively.
 * Please refer to the README.txt file for instructions on how to use this utility.
 * DO NOT USE THIS FILE DIRECTLY.
 * 
 * The program works through 2 phases, preprocessing and execution.
 * During the preprocessing phase, the input parameters (from the command line) are
 * searched for valid flags and arguments, outputting errors upon finding any invalid options.
 * Additional steps like opening the input file and defining the directories are also done here.
 * 
 * The execution phase consists of conducting the appropriate action depending on the
 * parameters defined during the preprocessing phase, this includes printing, copying and moving
 * files. The copying/moving actions can also be done in force mode, ensuring that files are
 * copied and moved, even if a file with the same name is in the target directory.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

// Headers defined
int search(char *key, char *arr[], int arrLen);
int isPath(char *path);
void writeToFile(int inFile, int outFile);
int invalidFlagsExist(int argc, char *argv[]);
int main(int argc, char *argv[]);

/*
 * Function: main
 * ----------------
 *   Main function that does conducts the preprocessing and execution steps
 * 
 *   argc: int representing the number of arguments
 *   argv: array of pointers for command line variables
 * 
 *   returns: Exit code   
 */
int main(int argc, char *argv[]) {
    int inFile, outFile;
    char *dir = "./logfile.txt";
    char *filename = "logfile.txt";
    char *msg;
    char *targetDir;
    
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
            // Compose 'clean' version of target directory using basename and dirname
            char* dirPart = dirname(strdup(argv[dIndex+1]));
            char* filePart = basename(strdup(argv[dIndex+1]));
            targetDir = strcat(strcat(dirPart, "/"), filePart);
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
    if ((inFile = open(dir, O_RDONLY)) < 0) {
        msg = "fileutil: file could not be opened\n";
        write(2, msg, strlen(msg));
        exit(1);
    }

    // EXECUTION PHASE
    if (dIndex != -1) {
        // -d present
        char* outpath = strcat(strcat(targetDir, "/"), filename);

        // exit if moving/copying a file from a directory to the same directory
        if (strcmp(outpath, dir) == 0) {
            msg = "fileutil: destination directory is the same as "
                  "the source directory\n";
            write(2, msg, strlen(msg));
            exit(1);
        } 

        // attempt to open output file
        int tries = 0;
        while ((outFile = open(outpath, O_WRONLY | O_CREAT | O_EXCL, 00700)) < 0) {
            if (fIndex != -1 && tries == 0) {
                // if in force mode, unlink file and try again
                msg = "fileutil: FORCE MODE ACTIVE\n";
                write(1, msg, strlen(msg));
                close(outFile);
                unlink(outpath);
                tries += 1;
            } else {
                // close file and exit
                msg = "fileutil: destination directory already has a file with the "
                      "same name as the source file OR directory does not exist\n";
                write(2, msg, strlen(msg));
                exit(2);
            }
        }

        writeToFile(inFile, outFile);

        // if moving the file, delete the original file
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
        // print file to stdout
        writeToFile(inFile, 1);        
    } else if (fIndex != -1) {
        // -F present only -> error
        msg = "fileutil: invalid argument, -F is redundant as nothing to force here! \n";
        write(2, msg, strlen(msg));
        exit(1);
    } else {
        // -F OR -M present only -> error
        msg = "fileutil: invalid argument, no destination to move the file! \n";
        write(2, msg, strlen(msg));
        exit(1);
    }

    // close all files and exit with code 0
    close(inFile);
    close(outFile);
    exit(0);
}

/*
 * Function: writeToFile
 * ------------------------
 * Writes from one file to another. Done by continuously reading from the input
 * file and pushing it to the output file.
 * 
 * inFile: file descriptor of the input file
 * outFile: file descriptor of the output file
 * 
 * returns: void
 */
void writeToFile(int inFile, int outFile) {
    ssize_t inbytes, outbytes;
    size_t nbytes = 1024;
    char buffer[nbytes];

    // put cursor at start of file
    lseek(inFile, 0, SEEK_SET);
    while ((inbytes = read(inFile, buffer, nbytes)) != 0) {
        outbytes = write(outFile, buffer, inbytes);

        if (outbytes == 0) break;
    }
}

/*
 * Function: search
 * ------------------------
 * Searches for a target string inside an array
 * 
 * key: string to locate in array
 * arr: array of pointers to locate the string in
 * arrLen: int for the size of array
 * 
 * returns: first located index of key, if not located returns -1
 */
int search(char *key, char *arr[], int arrLen) {
    for (int i = 0; i < arrLen; i++) {
        if (strcmp(key, arr[i]) == 0) {
            return i;
        }
    } 
    return -1;
}

/*
 * Function: isPath
 * ------------------
 * checks if a given string is a path
 * 
 * path: string representing input path to be checked
 * 
 * returns: 0 if the string is a path, not 0 otherwise
 */
int isPath(char *path) {
    char firstChar = path[0];
    return strcmp(&firstChar, "/");
}

/*
 * Function: invalidFlagsExist
 * -----------------------------
 * checks if invalid flags exist inside the arguments
 * 
 * argc: int representing the number of arguments
 * argv: array of pointers for command line variables
 * 
 * returns: 1 if the command line has invalid flag, 0 otherwise
 */
int invalidFlagsExist(int argc, char *argv[]) {
    int fCount, dCount, mCount;

    // loop over command arguments
    for (int i = 1; i < argc; i++) {
        if (isPath(argv[i]) == 0) {
            // allow it to be the first argument
            // also allow if -d flag is beforehand
            if (i != 1 && strcmp("-d", argv[i-1]) != 0) {
                return 1;
            }
        } else if (strcmp("-F", argv[i]) == 0) {
            fCount += 1;
        } else if (strcmp("-M", argv[i]) == 0) {
            mCount += 1;
        } else if (strcmp("-d", argv[i]) == 0) {
            dCount += 1;
        } else {
            return 1;
        }

        // if any count of valid flag surpasses 1, its invalid 
        if (fCount > 1 || dCount > 1 || mCount > 1) return 1;
    }

    return 0;
}
