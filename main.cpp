#include "cpu.h"

int main() {
    struct CPU cpu = {};
    cpu_ctor(&cpu);
    scanf_bfile(&cpu);
    cpu_dtor(&cpu);
    return 0;
}