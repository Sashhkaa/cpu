#ifndef ASM_H
#define ASM_H

#include "../common/text.h"
#include "../common/commands.h" 

struct Asm {
    struct Onegin text = {};
    int* arr ;
    int size_arr = 0;
    //int* commands;
};


void Asm_ctor(struct Asm* assm);
void Asm_dtor(struct Asm* assm);
int check_command(char* string);
char* remove_position_in_func(char* string);
void print_to_bfile(struct Asm* assm);
void remove_comments(struct Asm* assm);
char* skip_sp(char* str);
void read_strings(struct Text* text);


#endif // ASM_H
