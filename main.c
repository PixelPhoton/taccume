#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define TAPE_LEN (2048)

char* codeBuf;                  // buffer to store input code
int dataTape[TAPE_LEN];         // tape array

int accumulator = 0;            // accumulator

size_t codeLen;                 // length of code
size_t codePtr = 0;             // ptr to current char of code
unsigned short tapePtr = 0;     // ptr to current tape
char codePtrDirection = 1;      // negative if going left

void incrCodePtr() {
    codePtr += codePtrDirection;
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

    memset(dataTape, 0, sizeof(dataTape));    // initialise tape to 0
    codeLen = trgFStat.st_size - 1;

    while(codeBuf[codePtr] != ';') {
        switch(codeBuf[codePtr]) {
        case '>':
            tapePtr++;
            tapePtr %= TAPE_LEN;
            break;

        case '<':
            tapePtr--;
            tapePtr %= TAPE_LEN;
            break;

        case '+':
            dataTape[tapePtr]++;
            break;

        case '-':
            dataTape[tapePtr]--;
            break;

        case '^':
            accumulator = dataTape[tapePtr];
            break;

        case 'v':
            dataTape[tapePtr] = accumulator;
            break;

        case '!':
            accumulator = !accumulator;
            break;

        case '=':
            accumulator = (accumulator == dataTape[tapePtr]);
            break;

        case '#':
            accumulator = codePtr;
            break;

        case '[':
            if(accumulator) {
                codePtr += dataTape[tapePtr];
                codePtr %= codeLen;
                continue;
            }
            break;

        case ']':
            if(accumulator) {
                codePtr -= dataTape[tapePtr];
                codePtr %= codeLen;
                continue;
            }
            break;

        case 'T':
            if(accumulator) {
                codePtr += dataTape[tapePtr];
            } else {
                codePtr -= dataTape[tapePtr];
            }
            codePtr %= codeLen;
            continue;

        case ')':
            if(accumulator && codePtrDirection > 0) codePtrDirection *= -1;
            break;

        case '(':
            if(accumulator && codePtrDirection < 0) codePtrDirection *= -1;
            break;

        case '|':
            if(accumulator) codePtrDirection *= -1;
            break;

        case '*':
            printf("%i", dataTape[tapePtr]);
            break;

        case '.':
            putchar(dataTape[tapePtr]);
            break;

        case ',':
            dataTape[tapePtr] = getchar();
            break;

        case '_':
            codeBuf[codePtr] = (accumulator % 256);
            break;

        case 's':
            dataTape[tapePtr] -= accumulator;
            break;

        case 'a':
            dataTape[tapePtr] += accumulator;
            break;

        case 'm':
            dataTape[tapePtr] *= accumulator;
            break;

        case 'd':
            dataTape[tapePtr] /= accumulator;
            break;

        case ';':
            goto endOfProgram;

        case ':':
            if(accumulator) goto endOfProgram;

        case '\'':
            incrCodePtr();
            dataTape[tapePtr] = codeBuf[codePtr];
            break;

        case '"':
            incrCodePtr();
            while(codeBuf[codePtr] != '"') {
                putchar(codeBuf[codePtr]);
                incrCodePtr();
            }
            break;

        default:
            break;
        }

        incrCodePtr();
    }

endOfProgram:
    // end of pawgram uwu
    free(codeBuf);

    return 0;
}
