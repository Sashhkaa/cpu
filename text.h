#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <assert.h>
#include <stdint.h>

struct String {             // buffer
    char* str = nullptr;
    size_t len = 0;
};

struct Text {               //  text
    struct String* strings = nullptr;
    size_t size = 0;
};

struct Onegin { 
    FILE* file;
    struct String buffer;
    struct Text text;
};

enum ERR {
    CANT_CALLOC_MEMORY_FOR_BUFFER  = 1,
    CANT_CALLOC_MEMORY_FOR_TEXT    = 2,
    FSEEK_CANT_SET                 = 3,
    FTELL_CANT_COUNT               = 4,
    FREAD_CANT_READ_BUFFER         = 5,
};

int onegin_ctor(struct Onegin* cpu, const char* name);
FILE* open_file(const char* name);
long size_file(FILE* fp);
int buffer_filling(struct String* buffer, FILE* file);
void text_filling(struct String* buffer, struct Text* text);
void onegin_dtor(struct Onegin* onegin);

#endif // TEXT_H




