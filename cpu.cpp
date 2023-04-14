#include "cpu.h"
#include "assert.h"

void cpu_ctor(struct CPU* cpu){
    for (int i = 0; i < 4; i++) {
        cpu->reg[i] = 0;
    }

    STACK_CTOR(&(cpu->stack), 10);

    printf("size of stack = %d\n", cpu->stack.size);

    cpu->file = fopen("binary.txt", "rb");
    assert(cpu->file);

    cpu->size_arr = size_file(cpu->file) / 4;

    printf("size arr = %d\n", cpu->size_arr);

    cpu->arr =(char*)calloc(cpu->size_arr, sizeof(int));
}

void scanf_bfile (struct CPU* cpu) {
    
    for (int i = 0; i < cpu->size_arr; i++ ) {
        fread(cpu->arr, cpu->size_arr, sizeof(int), cpu->file);
    }
    
    for (int i = 0; i < cpu->size_arr; i++) {
        printf("%d\n", ((int*)cpu->arr)[i]);
    }
    
    printf("size_arr = %d\n", cpu->size_arr);
    printf("cpu->stack.size =  %d\n", cpu->stack.size);

    for (int i = 0; i < cpu->size_arr; i++) {
        switch(((int*)cpu->arr)[i]) {
        
            case PUSH:
            {   
                i++;
                printf("i = %d\n", i);
                stack_push(&cpu->stack, ((int*)cpu->arr)[i]);
                for (int l = 0; l < cpu->stack.size; l++) {
                    printf("stack->data[%d] = %d\n", i, cpu->stack.data[l - 1]);
                }
                printf("cpu->arr[i] = %d\n", ((int*)cpu->arr)[i]);
                STACK_OK(&cpu->stack);  //no error
                printf("push\n");
                printf("cpu->stack.size_in_puh =  %d\n", cpu->stack.size);
                break;
            }

            case POP:
            {   
                printf("before_pop");
                stack_pop(&cpu->stack);
                printf("pop\n");
                break;
            }

            case IN:
            {
                int number = 0;
                scanf("%d", &number);
                stack_push(&cpu->stack, number);
                printf("in\n");
                break;
            }

            case MUL:
            {   printf("ITS IN MUL");
                printf("cpu->stack.size =  %d\n", cpu->stack.size);
                int a = stack_pop(&cpu->stack);
                int b = stack_pop(&cpu->stack);
                printf("a and b = %d %d\n", a, b);
                stack_push(&cpu->stack, a * b);
                printf("mul\n");
                break;
            }

            case ADD: 
            {    printf("it's in ADD\n");           
                int a = (int)stack_pop(&cpu->stack);
                int b = (int)stack_pop(&cpu->stack);
                STACK_OK(&cpu->stack);

                printf("a = %d\n", a);
                printf("b = %d\n", b);


                stack_push(&cpu->stack, a + b);
                printf("add\n");
                break;
            }

            case SUB:
            {
                int a = stack_pop(&cpu->stack);
                int b = stack_pop(&cpu->stack);
                stack_push(&cpu->stack, a - b);
                printf("sub\n");
                break;
            }

            case DIV:
            {
                int a = stack_pop(&cpu->stack);
                int b = stack_pop(&cpu->stack);
                stack_push(&cpu->stack, a / b);
                printf("div\n");
                break;
            }

            case OUT: {
                int a = stack_pop(&cpu->stack);
                printf("%d\n", a);
                printf("out\n");
                break;
            }
        }
    }
    printf("hello jopa\n");
    fclose(cpu->file);
}

void cpu_dtor(struct CPU* cpu){
    for(int i = 0; i < 4; i++) {
        cpu->reg[i] = 0;
    }

    stack_dtor(&cpu->stack);

    cpu->file = nullptr;

    cpu->size_arr = 0;

    free(cpu->arr);
    
    cpu->arr = nullptr;
}

// регистры     //
//  сигнатура // 






