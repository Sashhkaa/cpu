#include "cpu.h"

void scanf_bfile (FILE* file, struct Stack* stack) {
    int size = size_file(file);

    int* arr = (int*)calloc(size, sizeof(char));

    fread((int*)arr, sizeof(int), size, file);
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == PUSH) {
            stack_push(stack, arr[i + 1]);
            i++;
        }
        if (arr[i] == POP) {
            stack_pop(stack);
        }
        if (arr[i] == IN) {
            int number = 0;
            scanf("%d", &number);
            stack_push(stack, number);
        }
        if (arr[i] == MUL) {
            int a = stack_pop(stack);
            int b = stack_pop(stack);
            stack_push(stack, a * b);
        }
        if (arr[i] == ADD) {
            int a = stack_pop(stack);
            int b = stack_pop(stack);
            stack_push(stack, a + b);
        }
        if (arr[i] == SUB) {
            int a = stack_pop(stack);
            int b = stack_pop(stack);
            stack_push(stack, a - b);
        }
        if (arr[i] == DIV) {
            int a = stack_pop(stack);
            int b = stack_pop(stack);
            stack_push(stack, a / b);
        }
        if (arr[i] == OUT) {
            int a = stack_pop(stack);
            printf("%d\n", a);
        }


    }
    free(arr);
}
