#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BYTES_LEN (1024)

char* codeBuf;      // buffer to store input code
char bytes[BYTES_LEN];   // byte array

size_t codeLen;                 // length of code
size_t codePtr = 0;             // ptr to current char of code
unsigned short bytePtr = 0;     // ptr to current byte

void incrCodePtr() {
    codePtr++;
    codePtr %= codeLen;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        puts("Heeyyyy give me one arg, u silly!\n(that arg being the file u wanna run)\n");
        exit(1);
    }

    struct stat trgFStat;   // stat of target file
    if(stat(argv[1], &trgFStat)) {
        perror("stat: ");
        exit(1);
    }

    FILE* inptFile = fopen(argv[1], "r");     // input code file
    if(!inptFile) {
        perror("fopen: ");
        exit(1);
    }

    // read from da file
    codeBuf = malloc(trgFStat.st_size);
    fread(codeBuf, 1, trgFStat.st_size-1, inptFile);

    fclose(inptFile);   // we done with it

    memset(&bytes, 0, 1024);    // initialise bytes to 0
    codeLen = trgFStat.st_size - 1;

    while(codeBuf[codePtr] != ';') {
        switch(codeBuf[codePtr]) {
        case '>':
            bytePtr++;
            bytePtr %= BYTES_LEN;
            incrCodePtr();
            break;

        case '<':
            bytePtr--;
            bytePtr %= BYTES_LEN;
            incrCodePtr();
            break;

        case '+':
            bytes[bytePtr]++;
            incrCodePtr();
            break;

        case '-':
            bytes[bytePtr]--;
            incrCodePtr();
            break;

        case ']':
            codePtr -= bytes[bytePtr];
            codePtr %= codeLen;
            break;

        case '[':
            codePtr += bytes[bytePtr];
            codePtr %= codeLen;
            break;

        case '.':
            putchar(bytes[bytePtr]);
            incrCodePtr();
            break;

        case ',':
            bytes[bytePtr] = getchar();
            incrCodePtr();
            break;

        default:
            incrCodePtr();
            break;
        }
    }

    // end of pawgram uwu
    free(codeBuf);

    return 0;
}
