DEF_CMD(PUSH, 1, 4, {
    printf("i_1 = %d\n", i);
    PUSHfunc(cpu->arr + i, cpu);
    i += SIZE_COMMAND + SIZE_NUMBER;
    printf("i_1 = %d\n", i);
})

DEF_CMD(PUSHR, 129, 5, {
    printf("i in -127 = %d\n", i);
    PUSHfunc(cpu->arr + i, cpu);
    i += SIZE_COMMAND + SIZE_REG;
})


DEF_CMD(POP, 2, 3, {
    POPfunc(cpu->arr + i, cpu);
                i += SIZE_COMMAND;
})

DEF_CMD(POPR, 130, 4, {
    printf("i in 130 mode = %d\n", i);
    POPfunc(cpu->arr + i, cpu);
    for (int k = 0; k < 4; k++) {
        printf("reg[%d] = %d\n", k, cpu->reg[k]);
    }
    i += SIZE_COMMAND + SIZE_REG;
})

DEF_CMD(IN, 3, 2, {
    int number = 0;
    scanf("%d", &number);
    stack_push(&cpu->stack, number);
    i += SIZE_COMMAND;
})

DEF_CMD(MUL, 4, 3, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    stack_push(&cpu->stack, a * b);
    i += SIZE_COMMAND;
})

DEF_CMD(ADD, 5, 3, {                 
    Elem_t a = stack_pop(&cpu->stack);          
    Elem_t b = stack_pop(&cpu->stack);
    stack_push(&cpu->stack, a + b);
    i += SIZE_COMMAND;
})

DEF_CMD(SUB, 6, 3, {
    Elem_t a = stack_pop(&cpu->stack);
    Elem_t b = stack_pop(&cpu->stack);
    stack_push(&cpu->stack, a - b);
    i += SIZE_COMMAND;
} )

DEF_CMD(DIV, 7, 3, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    stack_push(&cpu->stack, a / b);
    i += SIZE_COMMAND;
})

DEF_CMD(OUT, 8, 3, {
    int a = stack_pop(&cpu->stack);
    printf("%d\n", a);
    i += SIZE_COMMAND;
})

DEF_CMD(JP, 9, 2, {
    i = cpu->arr[i + SIZE_COMMAND]; 
})

DEF_CMD(JE, 10, 2, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    if (a == b) {
         i = cpu->arr[i + SIZE_COMMAND];
    }
    else return;
})

DEF_CMD(JA, 11, 2, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    if (a > b) {
         i = cpu->arr[i + SIZE_COMMAND];
    }
    else return;
})

DEF_CMD(JB, 12, 2, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    if (a < b) {
         i = cpu->arr[i + SIZE_COMMAND];
    }
    else return;
})

// PUSH [rax]
// PUSH [7]
// PUSH [rax + 8]
// PUSH [8 + rax]

// POP [rax]
// POP [8]
// POP [rax + 8]

DEF_CMD(JBE, 13, 2, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    if (a <= b) {
         i = cpu->arr[i + SIZE_COMMAND];
    }
    else return;
})

DEF_CMD(JAE, 14, 2, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    if (a >= b) {
         i = cpu->arr[i + SIZE_COMMAND];
    }
    else return;
})


DEF_CMD(JNE, 15, 2, {
    int a = stack_pop(&cpu->stack);
    int b = stack_pop(&cpu->stack);
    if (a != b) {
         i = cpu->arr[i + SIZE_COMMAND];
    }
    else return;
})

DEF_CMD(CALL, 16, 4, {
    stack_push(&cpu->stack, *(cpu->arr + i + SIZE_COMMAND + SIZE_NUMBER));
    i = cpu->arr[i + SIZE_COMMAND];
})

DEF_CMD(RETURN, 17, 6, {
    i += SIZE_COMMAND;
    i = stack_pop(&cpu->stack);
})

DEF_CMD(HLT, 18, 3, {
    return;
})