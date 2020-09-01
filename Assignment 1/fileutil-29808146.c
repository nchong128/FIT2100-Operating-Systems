#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int search(char *key, char *arr[], int arrLen);
char* findFileName(char *dir);

int main(int argc, char *argv[]) {
    int infile, dupfile;
    ssize_t inbytes, outbytes;
    size_t nbytes = 1024;
    char buffer[nbytes], *dir = "logfile.txt", *msg;
    char *filename;

    // If file path specified, use argv[1]
    // If no file path specified, uses logfile.txt
    if (argc > 1) {
        char firstChar = argv[1][0];
        if (strcmp(&firstChar, "/" ) == 0) {
            dir = argv[1];
        }
        filename = findFileName(dir);
        printf("filename: %s\n", filename);
    }

    // Opens file
    if ((infile = open(dir, O_RDONLY)) < 0) {
        // close files
        perror("logfile.txt could not be opened\n");
        exit(1);
    }

    // TASK 2
    // Loop over file and print outputs
    while ((inbytes = read(infile, buffer, nbytes)) != 0) {
        outbytes = write(1, buffer, inbytes);

        if (outbytes == 0) {
            break;
        }
    }
    write(1, "\n", 2);


    // TASK 3
    int dPos = search("-d", argv, argc);
    printf("%d\n", dPos);
    if (argc > 2) {
        char firstChar = argv[dPos+1][0];
        if (strcmp(&firstChar, "/" ) == 0) {
            // append file name to end
            // char targetDir = strcat(argv[dPos+1], );

            if ((dupfile = open("/mnt/c/Users/nchon/Documents/FIT2100/Assignment\\ 1/empty.txt", O_WRONLY | O_CREAT | O_EXCL)) < 0) {
                // close files
                perror("Destination directory already has a file with the same name as the source file OR directory does not exist");
                exit(2);
            }

            // Copy infile to dupfile
            lseek(infile, 0, SEEK_SET);
            while ((inbytes = read(infile, buffer, nbytes)) != 0) {
                outbytes = write(dupfile, buffer, inbytes);
                if (outbytes == 0) break;
            }
            
        }
    }



    msg = "Copy successful\n";
    write(1, msg, strlen(msg));

    close(infile);
    close(dupfile);
    exit(0);

}

int search(char *key, char *arr[], int arrLen) {
    // Returns first located index of key
    // If not in arr, returns -1
    int i;

    for (i = 0; i < arrLen; i++) {
        if (strcmp(key, arr[i]) == 0 ) {
            return i;
        }
    } 
    return -1;
}

char* findFileName(char *dir) {
    // finds the last backslash in the dir string
    // returns a copy of the string onwards
    dir = "/mnt/c/Users/nchon/Documents/FIT2100/Assignment\\ 1/empty.txt";
    char *filename = "";

    for (int i = strlen(dir)-1; i >= 0; i-- ) {
        if (strcmp(&dir[i],"/") == 0) {
            return strncpy(filename, dir+i+1, strlen(dir)-i-1);
        }
    }
    
    return filename;
}