#ifndef CPU_H
#define CPU_H


#include "../common/text.h"
#include "../common/stack.h"
#include "../common/commands.h"
#include "../asm/asm.h"

struct CPU {
    int reg[4] = {};
    struct Stack stack {};
    FILE* file = nullptr;
    int size_arr = 0;
    char* arr = nullptr;
};


void cpu_ctor(struct CPU* cpu);
void scanf_bfile (struct CPU* cpu);
void cpu_dtor(struct CPU* cpu);
#endif // CPU_H
