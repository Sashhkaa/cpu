#include "text.h"

int onegin_ctor(struct Onegin* onegin, const char* name) {
    onegin->file = open_file(name);

    onegin->buffer.len = size_file(onegin->file);

    onegin->buffer.str = (char*)calloc((onegin->buffer.len + 1), sizeof(char));
    if (onegin->buffer.str == nullptr){
        return CANT_CALLOC_MEMORY_FOR_BUFFER;
    }

    onegin->text.size = buffer_filling(&onegin->buffer, onegin->file); // кол-во строчек

    onegin->text.strings = (struct String*)calloc(onegin->text.size, sizeof(struct String));
    if (onegin->text.strings == nullptr) {
        return CANT_CALLOC_MEMORY_FOR_TEXT;
    }

    text_filling(&onegin->buffer, &onegin->text);
    

    fclose(onegin->file);
    onegin->file = nullptr;

    return 0;
}


FILE* open_file(const char* name) {
    FILE* fp = fopen(name,"rb");
    if (fp == nullptr) {
        printf("couldn't be open\n");
    }
    return fp;
}

long size_file(FILE* fp) {
    assert(fp);

    rewind(fp);

    if (fseek(fp, 0, SEEK_END) != 0) {
        return FSEEK_CANT_SET;
    }


    long position = ftell(fp);
    
    if (position == -1L) {
        return FTELL_CANT_COUNT;
    }

    rewind(fp);

    return position;
}


int buffer_filling(struct String* buffer, FILE* file) {
    assert(buffer);
    assert(file);

    int res = fread(buffer->str, sizeof(char), buffer->len, file);
    if (res != buffer->len) {
        return FREAD_CANT_READ_BUFFER;
    }

    buffer->str[buffer->len] = '\0';

    int count_string  = 0;
    char* current_ptr = buffer->str;

    while ((current_ptr = strchr(current_ptr, '\n')) != nullptr) {
        current_ptr++;
        count_string++;
    }

    return (buffer->str[buffer->len - 1] != '\n') ? count_string + 1 : 
                                                    count_string;
}

void text_filling(struct String* buffer, struct Text* text) {    
    assert(buffer);
    assert(text);
    
    char* current_pointer = buffer->str;
   
    for (size_t i = 0; i < text->size - 1; i++) {
        text->strings[i].str = current_pointer; 
        current_pointer = strchr(current_pointer,'\n');

        if ((current_pointer != buffer->str) && (*(current_pointer - 1) == '\r')) {
            *(current_pointer - 1) = '\0';
            text->strings[i].len = (int)(current_pointer - text->strings[i].str - 1);
        }
        else {
            *(current_pointer) = '\0';
            text->strings[i].len = (int)(current_pointer - text->strings[i].str);
        }

        current_pointer++;
    }

    text->strings[text->size - 1].str = current_pointer; 
    current_pointer = strchr(current_pointer,'\0');

    if ((current_pointer != buffer->str) && (*(current_pointer - 1) == '\n')) {
        if ((current_pointer - 1 != buffer->str) && (*(current_pointer - 2) == '\r')) {
            *(current_pointer - 2) = '\0';
            text->strings[text->size - 1].len = (int)(current_pointer - text->strings[text->size -1].str - 2);
        }
        else {
            *(current_pointer - 1) = '\0';
            text->strings[text->size - 1].len = (int)(current_pointer - text->strings[text->size -1].str - 1);
        }   
    }
    else {
        text->strings[text->size - 1].len = (int)(current_pointer - text->strings[text->size - 1].str);
    }
}



void onegin_dtor(struct Onegin* onegin) {
    free(onegin->buffer.str);
    onegin->buffer.str = nullptr;
    free(onegin->text.strings);
    onegin->text.strings = nullptr;
}
