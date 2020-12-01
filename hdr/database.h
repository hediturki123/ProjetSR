#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __DATABASE_H__
#define __DATABASE_H__

#define MAX_LINE 4096

typedef struct book_t {
    int ref;
    char author[64];
    char title[256];
    char genre[32];
} book_t;

char* getfield(char* line, int num);

int linesnb(FILE *f);

#endif // !__DATABASE_H__
