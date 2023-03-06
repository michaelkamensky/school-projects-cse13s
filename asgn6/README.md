# Lempel-Ziv Compression (Assignment 6)

## Description
In this assignment, I created a program that can compress text files using Lempel-Ziv 78 algorithm and then decompress it into the original file. The alogrith uses a dictionary. The compression dictionary will be created by using a trie which is a tree. For decompression the dictionary is an array. There will be two main programs that will encode the program and decode the program. The encoding executable will compress the file and write to a new file, and the decoding executable will decompress it into original content. Lempel-Ziv 78 is a lossless compression algorithm and therefore the final decompressed file should be indistinguishable from the original file.



This is a response to [assignment6](https://git.ucsc.edu/cse13s/winter2023-section01/resources/-/blob/main/asgn6/asgn6.pdf) in [Cse13s course](https://git.ucsc.edu/cse13s/winter2023-section01/resources)

## Installation
First you need to compile all appropirate c files to create sorting: run make as follows
```
make clean && make
```

## Usage
To run this program run encode as follows
```
./encode
```
You can use additional options.
The opitions can be seen with -h command:
```
SYNOPSIS
   encodes the file

USAGE
   ./encode [options]

OPTIONS
    -v : Print compression statistics to stderr
    -i <input> : Specify input to compress (stdin by default)
    -o <output> : Specify output of compressed input (stdout by default)
    -h : display program help and usage.
```
To run decode run as follows
```
./decode
```
You can use additional options.
The opitions can be seen with -h command:
```
SYNOPSIS
   decodes the file

USAGE
   ./decode [options]

OPTIONS
    -v : Print compression statistics to stderr
    -i <input> : Specify input to compress (stdin by default)
    -o <output> : Specify output of compressed input (stdout by default)
    -h : display program help and usage.
```

## False Positive from scan-build
scan-build complains about memory leak in memory pointed by in_file_name, out_file_name in both my main functions
I believe these reports to be false positives because at the end of each program I free all pointers to these files.
```
scan-build: Using '/usr/lib/llvm-14/bin/clang' for static analysis
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -c encode.c
encode.c:87:17: warning: Potential leak of memory pointed to by 'in_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
encode.c:87:17: warning: Potential leak of memory pointed to by 'out_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
2 warnings generated.
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -c trie.c
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -c word.c
word.c:13:5: warning: Null pointer passed to 2nd parameter expecting 'nonnull' [core.NonNullParamChecker]
    memcpy(word->syms, syms, word->len);
    ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1 warning generated.
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -c io.c
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -o encode encode.o trie.o word.o io.o
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -c decode.c
decode.c:77:17: warning: Potential leak of memory pointed to by 'in_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
decode.c:77:17: warning: Potential leak of memory pointed to by 'out_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
2 warnings generated.
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -o decode decode.o word.o io.o
scan-build: Analysis run complete.
scan-build: 3 bugs found.
scan-build: Run 'scan-view /tmp/scan-build-2023-03-06-192845-1455-1' to examine bug reports.
```

## Support
Please contact mkamensk@ucsc.edu if you need help or provide feedback for this project


## Author
Michael V. Kamensky
