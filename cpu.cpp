#include "cpu.h"
#include "assert.h"

#define CPUSIGN 14


void cpu_ctor(struct CPU* cpu){
    for (int i = 0; i < 4; i++) {
        cpu->reg[i] = 0;
    }

    STACK_CTOR(&(cpu->stack), 2);

    cpu->file = fopen("binary.txt", "rb");
    assert(cpu->file);

    cpu->size_arr = size_file(cpu->file) / sizeof(int);

    cpu->arr = (uint8_t*)calloc(cpu->size_arr * sizeof(int), sizeof(char));

    cpu->sign = CPUSIGN;
    
}

void PUSHfunc(uint8_t* pointer, struct CPU* cpu) {
    uint8_t* current_pointer = pointer; 
    printf("fkdfkdf = %d\n", *(current_pointer - 1));
    printf("fkdfkdf = %d\n", *(current_pointer));
    printf("fkdfkdf = %d\n", *(current_pointer + 1));

    if (*(current_pointer) == 129) {
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

void POPfunc(uint8_t* pointer, struct CPU* cpu) {
    uint8_t* current_pointer = pointer; 

    if (*current_pointer == 130) {
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
    
    fread(cpu->arr, cpu->size_arr + 1, sizeof(uint8_t), cpu->file);

    printf("size_arr = %d\n", cpu->size_arr);
    if (cpu->arr[0] != cpu->sign) {
        printf("version of the cpu cant connet to assembler");
        fclose(cpu->file);
        return;
    }
    for(int j = 0; j < cpu->size_arr + 1; j++) {
    printf("arr[%d] = %d\n",j, cpu->arr[j]);
    }
    for (int i = 0; i < cpu->size_arr + 1; i++) {
        switch((cpu->arr)[i]) {
            
            case 1:
            {   printf("push func\n");
                PUSHfunc(cpu->arr + i, cpu);
                i++;
                break;
            }

            case 129:

            {   printf("push func\n");
                PUSHfunc(cpu->arr + i, cpu);
                i++;
                break;
            }

            case 2:
            {   
                printf("pop_func\n");
                POPfunc(cpu->arr + i, cpu);
                break;
            }

            case 130:
            {   
                printf(" i in the 130 mode = %d\n", i);
                printf("pop_func in register mode\n");
                POPfunc(cpu->arr + i, cpu);
                for (int k = 0; k < 4; k++) {
                    printf("reg[%d] = %d\n", k, cpu->reg[k]);
                }
                i++;
                break;
            }
            case IN:
            {
                int number = 0;
                scanf("%d", &number);
                stack_push(&cpu->stack, number);
                break;
            }

            case MUL:
            {
                int a = stack_pop(&cpu->stack);
                int b = stack_pop(&cpu->stack);
                stack_push(&cpu->stack, a * b);
                break;
            }

            case ADD: 
            {           
                Elem_t a = stack_pop(&cpu->stack);          
                Elem_t b = stack_pop(&cpu->stack);
                stack_push(&cpu->stack, a + b);
                break;
            }

            case SUB:
            {
                Elem_t a = stack_pop(&cpu->stack);
                Elem_t b = stack_pop(&cpu->stack);
                stack_push(&cpu->stack, a - b);
                break;
            }

            case DIV:
            {
                int a = stack_pop(&cpu->stack);
                int b = stack_pop(&cpu->stack);
                stack_push(&cpu->stack, a / b);
                break;
            }

            case OUT: {
                int a = stack_pop(&cpu->stack);
                printf("%d\n", a);
                break;
            }
        }
    }
}

void cpu_dtor(struct CPU* cpu){
    for(int i = 0; i < 4; i++) {
        cpu->reg[i] = 0;
    }

    stack_dtor(&cpu->stack);

    cpu->file = nullptr;

    cpu->size_arr = 0;

    free(cpu->arr);

    for (int i = 0; i < 4; i++) {
        cpu->reg[i] = 0;
    }
    
    cpu->arr = nullptr;
}

// регистры                  //
// PUSH RAX                      
// режим в пуше после push 
// либо просто другой номер  (поднятие бита  129 - регистр, 1 - число )






