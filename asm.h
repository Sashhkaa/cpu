#ifndef ASM_H
#define ASM_H

#include "../common/text.h"
#include "../common/commands.h" 

#define ASMSIGN 14

struct Asm {
    struct Onegin data = {};
    char* arr = nullptr;
    int size_arr = 0;
    int sign = 0;
    int command_arr[3] = {4, 2, 3};
    char* lable = nullptr;
};


void Asm_ctor(struct Asm* assm);
void Asm_dtor(struct Asm* assm);
int check_command(char* string);
char* remove_position_in_func(struct Asm* assm, char* current_pointer, int a);
void print_to_bfile(struct Asm* assm);
void remove_comments(struct Asm* assm);
char* skip_sp(char* str);
void read_strings(struct Text* text);


#endif // ASM_H

// a = 1 + 2 + 4
// b = 1 + a + 5

// PUSH 1 
// PUSH 2  
// ADD     
// PUSH 4  
// ADD     
// POP RAX 
// PUSH 1
// PUSH RAX
// ADD
// PUSH 5                    rax
// ADD                   eax
// POP RBX           ax
   //                 al ah 
// байты с конца 0X AA 00 00 00 = 170
// биты как числа 0b00000100 = 4

//mov rax, QWORD:[0x1000]