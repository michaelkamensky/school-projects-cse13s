# Public Key Cryptography (Assignment 5)

## Description
This is a project that uses different c programs to encrypt and decrypt a file using a public and private key's. The keygen program gernerates a public and private key and stores them into two seperate files. The encrypt executable takes a public key and encrypts a file that is passed and saves it to another file. Finally the decrypt executable takes the private key from a file and decrypts an encrypted file and then writes the result to another file.

This is a response to [assignment5](https://git.ucsc.edu/cse13s/winter2023-section01/resources/-/blob/main/asgn5/asgn5.pdf) in [Cse13s course](https://git.ucsc.edu/cse13s/winter2023-section01/resources)

## Installation
First you need to compile all appropirate c files to create sorting: run make as follows
```
make clean && make
```

## Usage
To run this program run keygen as follows
```
./keygen
```
You can use additional options.
The opitions can be seen with -h command:
```
SYNOPSIS
   Creates a public and private key

USAGE
   ./keygen [options]

OPTIONS
    -b : specifies the minimum bits needed for the public modulus n
    -i : specifies the number of Miller-Rabin iterations for testing primes (default: 50)
    -n pbfile : specifies the public key file (default: ss.pub)
    -d pvfile : specifies the private key file (default: ss.priv)
    -s : specifies the random seed for the random state initialization
    -v : enables verbose output
    -h : display program help and usage
```
To run encrypt run as follows
```
./encrypt
```
You can use additional options.
The opitions can be seen with -h command:
```
SYNOPSIS
   encrypts file

USAGE
   ./encrypt [options]

OPTIONS
    -i input : specifices the input file to encrypt (default: stdin)
    -o output : specifies the output file to encrypt (default: stdout)
    -n : specifies the file containing the public key (default: ss.pub)
    -v : enables verbose output
    -h : display program help and usage.
```
To run decrypt run as follows
```
./decrypt
```
You can use additional options.
The opitions can be seen with -h command:
```
SYNOPSIS
   Decrypts file

USAGE
   ./decrypt [options]

OPTIONS
    -i input : specifices the input file to decrypt (default: stdin)
    -o output : specifies the output file to decrypt (default: stdout)
    -n : specifies the file containing the private key (default: ss.priv)
    -v : enables verbose output
    -h : display program help and usage.

```

## False Positive from scan-build
scan-build complains about memory leak in memory pointed by private_key_file_name, in_file_name, out_file_name, public_key_file_name
I believe these reports to be false positives because at the end of each program I free all pointers
```
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -c decrypt.c
decrypt.c:36:17: warning: Potential leak of memory pointed to by 'private_key_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
decrypt.c:36:17: warning: Potential leak of memory pointed to by 'in_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
decrypt.c:36:17: warning: Potential leak of memory pointed to by 'out_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
3 warnings generated.
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -c randstate.c
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -c numtheory.c
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -c ss.c
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -o decrypt decrypt.o randstate.o numtheory.o ss.o -lgmp
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -c encrypt.c
encrypt.c:37:17: warning: Potential leak of memory pointed to by 'public_key_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
encrypt.c:37:17: warning: Potential leak of memory pointed to by 'in_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
encrypt.c:37:17: warning: Potential leak of memory pointed to by 'out_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "hvn:i:o:")) != -1) {
                ^~~~~~
3 warnings generated.
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -o encrypt encrypt.o randstate.o numtheory.o ss.o -lgmp
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -c keygen.c
keygen.c:43:17: warning: Potential leak of memory pointed to by 'private_key_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "b:i:n:d:s:vh")) != -1) {
                ^~~~~~
keygen.c:43:17: warning: Potential leak of memory pointed to by 'public_key_file_name' [unix.Malloc]
    while ((c = getopt(argc, argv, "b:i:n:d:s:vh")) != -1) {
                ^~~~~~
2 warnings generated.
/usr/share/clang/scan-build-14/bin/../libexec/ccc-analyzer -Wall -Wpedantic -Werror -Wextra -g  -o keygen keygen.o randstate.o numtheory.o ss.o -lgmp
scan-build: Analysis run complete.
scan-build: 5 bugs found.

```

## Support
Please contact mkamensk@ucsc.edu if you need help or provide feedback for this project


## Author
Michael V. Kamensky
