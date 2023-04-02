#ifndef ASM_H
#define ASM_H

#include "../common/text.h"
#include "../common/commands.h"

int check_command(const char* string);
void print_to_bfile(struct Text* text);
void read_strings(struct Text* text);


#endif // ASM_H
