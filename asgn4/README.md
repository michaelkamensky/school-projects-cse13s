# The Game of Life (Assignment 4)

## Description
This is a project that runs the game of life. The game works by having a 2d grid of alive and dead cells. Each generation or iteration of the program checks every cell. If an alive cell has two or three live neighbors it lives. If a dead cell has exactly three cells it becomes alive. All other cells become dead. Then the program runs through the many iterations of generations of the board. The project can take an input file and can retrun an out put file, and has a toroidal mode and ncurses mode.

This is a response to [assignment 4](https://git.ucsc.edu/cse13s/winter2023-section01/resources/-/blob/main/asgn4/asgn4.pdf) in [Cse13s course](https://git.ucsc.edu/cse13s/winter2023-section01/resources)

## Installation
First you need to compile all appropirate c files to create sorting: run make as follows
```
make clean && make
```

## Usage
To run this program run life as follows
```
./life [options]                                           
```
You can use indvidual tests using additional options.
The opitions can be seen with -h command:
```
SYNOPSIS
   Runs the game of life

USAGE
   ./life [options]

OPTIONS
    -t : Specify that the Game of Life is to be played on a toroidal universe.
    -s : Silence ncurses.
    -n generations : Specify the number of generations that the universe goes through. The default number of generations is 100.
    -i input : Specify the input file to read in order to populate the universe. By default the input should be stdin
    -o output :  Specify the output file to print the final state of the universe to. By default the output should be stdout.
    -h : display program help and usage.
```

## False Positive from valgrind
I observed that valgrind found 3 possible memory leaks in ncurses initscr() when no -s option is used.
It is not a problem with my program.
```
==4739==
==4739== HEAP SUMMARY:
==4739==     in use at exit: 120,611 bytes in 192 blocks
==4739==   total heap usage: 248 allocs, 56 frees, 136,186 bytes allocated
==4739==
==4739== 9 bytes in 1 blocks are possibly lost in loss record 9 of 69
==4739==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4739==    by 0x496660E: strdup (strdup.c:42)
==4739==    by 0x489FBE4: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3)
==4739==    by 0x48A2F28: _nc_tiparm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3)
==4739==    by 0x4873238: newterm_sp (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x4873B4C: newterm (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x4873BDF: initscr (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x109592: main (life.c:124)
==4739==
==4739== 24 bytes in 1 blocks are possibly lost in loss record 27 of 69
==4739==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4739==    by 0x49DE14E: tsearch (tsearch.c:337)
==4739==    by 0x489FBFE: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3)
==4739==    by 0x48A2F28: _nc_tiparm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3)
==4739==    by 0x4873238: newterm_sp (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x4873B4C: newterm (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x4873BDF: initscr (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x109592: main (life.c:124)
==4739==
==4739== 168 bytes in 1 blocks are possibly lost in loss record 52 of 69
==4739==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==4739==    by 0x489FB5D: ??? (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3)
==4739==    by 0x48A2F28: _nc_tiparm (in /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3)
==4739==    by 0x4873238: newterm_sp (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x4873B4C: newterm (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x4873BDF: initscr (in /usr/lib/x86_64-linux-gnu/libncurses.so.6.3)
==4739==    by 0x109592: main (life.c:124)
==4739==
==4739== LEAK SUMMARY:
==4739==    definitely lost: 0 bytes in 0 blocks
==4739==    indirectly lost: 0 bytes in 0 blocks
==4739==      possibly lost: 201 bytes in 3 blocks
==4739==    still reachable: 120,410 bytes in 189 blocks
==4739==         suppressed: 0 bytes in 0 blocks
==4739== Reachable blocks (those to which a pointer was found) are not shown.
==4739== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==4739==
==4739== For lists of detected and suppressed errors, rerun with: -s
==4739== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)

```

## False Positive from scan-build
scan-build complains about memory leak in memory pointed by in\_file\_name and out\_file\_name.
I believe this report is a false positive because at the end of main I free both pointers
```
mkamensk@vera:~/cse13s/asgn4$ scan-build make
scan-build: Using '/usr/lib/llvm-14/bin/clang' for static analysis
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -O2   -c life.c
life.c:92:17: warning: Potential leak of memory pointed to by 'in_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "ahtsn:i:o:")) != -1) {
                ^~~~~~
life.c:92:17: warning: Potential leak of memory pointed to by 'out_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "ahtsn:i:o:")) != -1) {
                ^~~~~~
2 warnings generated.
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -O2   -c universe.c
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g -O2   -o life life.o universe.o  -lncurses
scan-build: Analysis run complete.
scan-build: 2 bugs found.
scan-build: Run 'scan-view /tmp/scan-build-2023-02-11-011233-4796-1' to examine bug reports.

```

## Support
Please contact mkamensk@ucsc.edu if you need help or provide feedback for this project

## Author
Michael V. Kamensky

