#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

/* 
 * create_random_file <filename> <total bytes> <block size>
 */
int main(int argc, char **argv) {
    const char* filename = argv[1]; // file name
    long n = (long)atoi(argv[2]); // total size
    long block_sz = (long)atoi(argv[3]); // block size

    int written_sz = 0; // keep track of how much written
    char buf[block_sz]; // buffer of size block size
    long sz;
    FILE *fp = fopen(filename, "w"); // file to write to

    long start = now(); // timer
    while(written_sz < n) { // written size does not exceed total size
        bzero(buf, block_sz); // zero out the buffer
        sz = (n-written_sz > block_sz) ? block_sz : (n - written_sz);
        // truncates extra bytes if there is not enough space
        random_array(buf, sz); // create a random array
        fwrite(buf, 1, sz, fp); 
        fflush(fp); // flush the buffer
        written_sz += sz;
    }
    long end = now(); // end timer

    fclose(fp);
    printf("block_sz=%ld milliseconds=%ld\n", block_sz, end-start);
}