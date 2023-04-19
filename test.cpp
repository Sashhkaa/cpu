#include "common/stack.h"

int main()
{
   struct  Stack* stk = (Stack*)calloc(1, sizeof(Stack));
   STACK_CTOR(stk, 2);

   stack_push(stk, 400);
   stack_push(stk, 800);
   stack_push(stk, 1200);
   stack_push(stk, 1600);
   stack_push(stk, 2000);
   
   return 0;
}