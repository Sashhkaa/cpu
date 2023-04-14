#include "cpu.h"

int main() {
    struct CPU cpu = {};
    cpu_ctor(&cpu);
    STACK_OK(&cpu.stack);
    printf("after ctor\n");
    scanf_bfile(&cpu);
    STACK_OK(&cpu.stack);
    cpu_dtor(&cpu);
    return 0;
}