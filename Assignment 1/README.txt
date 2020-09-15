FILEUTIL UTILITY C PROGRAM
AS PART OF: FIT2100 ASSIGNMENT 1 
WRITTEN BY: NICHOLAS CHONG

COMPILING
----------------------------------
In the current directory, enter...
$ make

This will generate a fileutil file.

USAGE
----------------------------------
The format is as follows:
$ ./fileutil [SOURCEFILE] [OPTIONS]

SOURCEFILE: absolute path of the file

OPTIONS:
-d destDir:
  Allows to input a path for the destination directory for copying or moving
  the source file. destDir must follow -d

-M: 
  Changes the behaviour of the -d argument to move the file instead of copying
  Only valid when used in conjunction with the -d ... argument

-F:
  Makes the program overwrite any file which has the same name as the source file
