#include "cpu.h"
#include "assert.h"

static const char CPUSIGN = 14;
static const size_t SIZE_STACK = 2;
static const size_t SIZE_COMMAND = sizeof(char);
static const size_t SIZE_REG = sizeof(char);
static const size_t SIZE_NUMBER = sizeof(int);

void cpu_ctor(struct CPU* cpu) {
    for (int i = 0; i < 4; i++) {
        cpu->reg[i] = 0;
    }

    STACK_CTOR(&(cpu->stack), SIZE_STACK);

    cpu->file = fopen("binary.txt", "rb");
    assert(cpu->file);

    cpu->size_arr = size_file(cpu->file) / sizeof(char);

    cpu->arr = (char*)calloc(cpu->size_arr, sizeof(char));

    cpu->sign = CPUSIGN;
}

void PUSHfunc(char* pointer, struct CPU* cpu) {
    char* current_pointer = pointer; 

    if (*current_pointer == (char)(129)) {
        current_pointer++;

        if (*current_pointer == 1) {
            printf("ax");
            stack_push(&cpu->stack, cpu->reg[0]);
        }

        if (*current_pointer == 2) {
            printf("bx");
            stack_push(&cpu->stack, cpu->reg[1]);
        }

        if (*current_pointer == 3) {
            printf("cx");
            stack_push(&cpu->stack, cpu->reg[2]);
        }

        if (*current_pointer == 4) {
            printf("dx");
            stack_push(&cpu->stack, cpu->reg[3]);
        }

    }

    if (*(current_pointer) == 1) {
        current_pointer++;
        stack_push(&cpu->stack, *(current_pointer));
    }

}

void POPfunc(char* pointer, struct CPU* cpu) {
    char* current_pointer = pointer; 

    if (*current_pointer == -126) {
        current_pointer++;

        if (*current_pointer == 1) {
            printf("ax\n");
            cpu->reg[0] = stack_pop(&cpu->stack);
        }

        if (*current_pointer == 2) {
            printf("bx\n");
            cpu->reg[1] = stack_pop(&cpu->stack);
        }

        if (*current_pointer == 3) {
            cpu->reg[2] = stack_pop(&cpu->stack);
        }

        if (*current_pointer == 4) {
            cpu->reg[3] = stack_pop(&cpu->stack);
        }

    }
    else {
        printf("pop in function in int mode\n");   
        stack_pop(&cpu->stack);
    }
}


void scanf_bfile (struct CPU* cpu) {
    printf("size arr = %d\n", cpu->size_arr);
    
    fread(cpu->arr, cpu->size_arr, sizeof(char), cpu->file);

    printf("size_arr = %d\n", cpu->size_arr);

    if (cpu->arr[0] != cpu->sign) {
        printf("version of the cpu cant connet to assembler");
        return;
    }

    for (int j = 0; j < cpu->size_arr; j++) {
        printf("arr[%d] = %d\n", j, cpu->arr[j]);
    }
    int i = 1;
    while(i < cpu->size_arr){
        switch((unsigned char)(cpu->arr)[i]) {

#           define DEF_CMD(name, number, len, ...) case name: {__VA_ARGS__} break;
#           include "../common/comm.h"
#           undef DEF_CMD
        }
    }
}

void cpu_dtor(struct CPU* cpu){
    for(int i = 0; i < 4; i++) {
        cpu->reg[i] = 0;
    }

    //free(cpu->stack.data);

    stack_dtor(&cpu->stack);


    fclose(cpu->file);
    cpu->file = nullptr;

    cpu->size_arr = 0;

    free(cpu->arr);
}








