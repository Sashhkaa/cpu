#include "cpu.h"

int main() {
    FILE* file = fopen("b_file.txt", "rb");
    struct Stack stack = {};
    STACK_CTOR(&stack,2);
    scanf_bfile(file, &stack);
    stack_dtor(&stack);
    fclose(file);
    return 0;
}