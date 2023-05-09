#ifndef CPU_H
#define CPU_H

#include "../common/text.h"
#include "../common/stack.h"

enum COMMANDS {
#   define DEF_CMD(name, number, len, ...) name = number,
#   include "../common/comm.h"
#   undef DEF_CMD
};

struct CPU {
    int reg[4] = {};
    struct Stack stack = {};
    FILE* file = nullptr;
    int size_arr = 0;
    char* arr = nullptr;
    int sign = 0; 
};

void cpu_ctor(struct CPU* cpu);
void PUSHfunc(char* pointer, struct CPU* cpu);
void POPfunc(char* pointer, struct CPU* cpu);
void scanf_bfile (struct CPU* cpu);
void cpu_dtor(struct CPU* cpu);

#endif // CPU_H
