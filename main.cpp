#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include "asm.h"

int main() {
    struct Asm assm = {};
    Asm_ctor(&assm);
    print_to_bfile(&assm);
    Asm_dtor(&assm);
    return 0;
}