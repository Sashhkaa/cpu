#include "asm.h"
#include "assert.h"

void Asm_ctor(struct Asm* assm){
    onegin_ctor(&assm->data, "cpu.txt");

    assm->arr = (char*)calloc(100, sizeof(int)); // поменять, но мне лень думать
    assm->sign = ASMSIGN; 
    assm->jump.lable = (struct Lable*)calloc(10, sizeof(struct Lable));
    for (int i = 0; i < 10; i++) {
        assm->jump.lable[i].jump_start.jump_start = (int*)calloc(7, sizeof(int));
    }
}
char* remove_position_in_func(struct Asm* assm, char* current_pointer, int cmd) {
    switch (cmd)
    {
#       define DEF_CMD(name, number, len, ...) case name: return current_pointer + len;
#       include "../common/comm.h"
#       undef DEF_CMD

        default:
            return current_pointer;
    }
}

int check_command(char* string){
#   define DEF_CMD(name, number, len, ...) if (!strncmp(string, #name, len)) return number;
#   include "../common/comm.h"
#   undef DEF_CMD
    return UNKNOWN;
}

int lable_size_func(char* pointer, int mode) {   
    int size = 0;
    char* current_pointer = pointer;
    if (mode == 0) {
        while((*current_pointer != '\0')) {
            size++;
            current_pointer++;
        }
        return size;
    }

    else {
        while(*current_pointer != ':')  {
            current_pointer++;
            size++;
        }
        return size;
    }
}

void printf_lable_array(struct Asm* assm) {
    printf("size = %d\n", assm->jump.size);
    for (int i = 0; i < assm->jump.size ; i++) {
        printf("lable[%d].lable = %s\n", i, assm->jump.lable[i].lable);
        printf("lable[%d].jump_position = %d\n", i, assm->jump.lable[i].jump_pos);
        printf("lable[%d].jump_start    = %d\n", i, assm->jump.lable[i].jump_start.jump_start[0]);
    }
}

void jump_func(struct Asm* assm, char* pointer , int ip, int mode) {
    char* current_pointer = pointer; 
    current_pointer = skip_sp(current_pointer);
    int lable_size = 0;
    int flag = -1;

    if (mode == 0) {
        current_pointer = skip_sp(current_pointer);

        lable_size = lable_size_func(current_pointer, 0);

        if (*current_pointer == ':') {

            current_pointer = current_pointer + 1;
                
            for (int i = 0; i < assm->jump.size; i++) {
                if (strncmp(current_pointer, assm->jump.lable[i].lable, lable_size) == 0) { //встретила
                    flag = i;
                    break; 
                }
            }

            if (flag >= 0) { 
                assm->jump.lable[flag].jump_start.jump_start[assm->jump.lable[flag].jump_start.size] = ip;
                assm->jump.lable[flag].jump_start.size++;
            }
            else {
                assm->jump.lable[assm->jump.size].lable = current_pointer;
                assm->jump.lable[assm->jump.size].jump_start.jump_start[assm->jump.lable[assm->jump.size].jump_start.size] = ip;
                assm->jump.lable[assm->jump.size].jump_start.size++;
                assm->jump.size++;
            }
        }
        else printf("when using a label, it must be preceded by :");
    }
    else {
        current_pointer = skip_sp(current_pointer);

        lable_size = lable_size_func(current_pointer, 1);

        if(*(current_pointer + lable_size) == ':') {
            
            *(current_pointer + lable_size) = '\0';
           
            for (int i = 0; i < assm->jump.size; i++) {
                if (strncmp(current_pointer, assm->jump.lable[i].lable, lable_size) == 0) { //встретила
                    flag = i;
                    break;
                }
            }

            if (flag >= 0) {
                assm->jump.lable[flag].jump_pos = ip;
            }
            else {
                assert(assm->jump.lable);
                assm->jump.lable[assm->jump.size].lable = current_pointer;
                assm->jump.lable[assm->jump.size].jump_pos = ip;
                assm->jump.size++;
            }

        }
        else ("after lable it must to be :");  
    }
}


void poison_lable_filling(struct Lable* lable) {
    lable->lable = nullptr;
    lable->jump_pos = -1;

    for (int i = 0; i < lable->jump_start.size; i++) {
        lable->jump_start.jump_start[i] = -1;
    }
}

void second_bypass(struct Asm* assm) {
    for (int i = 0; i < assm->size_arr; i++) {
        if ((assm->arr[i] == JP) || (assm->arr[i] == CALL) || (assm->arr[i] == JE) || (assm->arr[i] == JNE) ||
        (assm->arr[i] == JA) || (assm->arr[i] == JAE) || (assm->arr[i] == JBE) || (assm->arr[i] == JA) || (assm->arr[i] == JB)) {
            for (int j = 0; j < assm->jump.size; j++) { 
                for (int k = 0; k < assm->jump.lable[j].jump_start.size; k++) {
                    if (i == assm->jump.lable[j].jump_start.jump_start[k]) {
                        *(int*)(assm->arr + i + sizeof(char)) = assm->jump.lable[j].jump_pos;
                        i += sizeof(int);
                    }
                }
            }
        }
    }
}

void print_to_bfile(struct Asm* assm) {
    assm->jump.size = 0;
    assm->size_arr  = 1;
    int command_name = 0;
    assm->arr[0] = (char)assm->sign;

    FILE* file_b = fopen("binary.txt", "wb");
    remove_comments(assm);

    for (int i = 0; i < assm->data.text.size; i++) {

        if (assm->data.text.strings[i].len == 0) {
            continue;
        }

        char* current_pointer = assm->data.text.strings[i].str;

        current_pointer = skip_sp(current_pointer);

        if (*current_pointer == '\0') {         
            continue;
        }

        command_name = check_command(current_pointer); 

        current_pointer = remove_position_in_func(assm, current_pointer, command_name);

        if (command_name == PUSH) {

            current_pointer = skip_sp(current_pointer);

            if (strncmp(current_pointer, "RAX", 3) == 0) {
                *(assm->arr + assm->size_arr) = 129;
                assm->size_arr += sizeof(char);
                *(assm->arr + assm->size_arr) = 1;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }

                assm->size_arr = assm->size_arr + sizeof(char);
                continue;
            }

            if (strncmp(current_pointer, "RBX", 3) == 0){
                *(assm->arr + assm->size_arr) = 129;
                assm->size_arr += sizeof(char);
                *(assm->arr + assm->size_arr) = 2;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }

                assm->size_arr += sizeof(char);
                continue;
            }

            if (strncmp(current_pointer, "RCX", 3) == 0){
                *(assm->arr + assm->size_arr) = 129;
                assm->size_arr += sizeof(char);
                *(assm->arr + assm->size_arr) = 3;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }

                assm->size_arr += sizeof(char);
                continue;
            }

            if (strncmp(current_pointer, "RDX", 3) == 0){

                *(assm->arr + assm->size_arr) = 129;
                assm->size_arr += sizeof(char);
                *(assm->arr + assm->size_arr) = 4;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                assm->size_arr += sizeof(char);
                continue;
            }

            else {
            int number = 0;
            sscanf(current_pointer, "%d", &number);

            *(assm->arr + assm->size_arr) = 1;
            assm->size_arr += sizeof(char);

            *((int*)(assm->arr + assm->size_arr)) = number;

            if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
            assm->size_arr += sizeof(int);
            continue;
            }
        }

        if (command_name == POP) {

            current_pointer = skip_sp(current_pointer);

            if (strncmp(current_pointer, "RAX", 3) == 0) {
                
                *(assm->arr + assm->size_arr) = 130;
                assm->size_arr++;
                *(assm->arr + assm->size_arr) = 1;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                assm->size_arr++;
                continue;
            }

            if (strncmp(current_pointer, "RBX", 3) == 0){

                *(assm->arr + assm->size_arr) = 130;
                assm->size_arr++;
                *(assm->arr + assm->size_arr) = 2;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                assm->size_arr++;
                continue;
            }

            if (strncmp(current_pointer, "RCX", 3) == 0) {

                *(assm->arr + assm->size_arr) = 130;
                assm->size_arr++;
                *(assm->arr + assm->size_arr) = 3;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                assm->size_arr++;
                continue;
            }

            if (strncmp(current_pointer, "RDX", 3) == 0) {

                *(assm->arr + assm->size_arr) = 130;
                assm->size_arr++;
                *(assm->arr + assm->size_arr) = 4;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                assm->size_arr++;
                continue;
            }
            else { 
                *(assm->arr + assm->size_arr)  = 2;
                assm->size_arr = assm->size_arr + sizeof(char);
            }
        }

        if (command_name == JP) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = JP;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }

        if (command_name == JE) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = JE;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }

        
        if (command_name == JA) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = JA;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }
        
        if (command_name == JAE) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = JE;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }
        
        if (command_name == JB) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = JE;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }

        if (command_name == JBE) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = JE;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }

        
        if (command_name == JNE) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = JE;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }

        if (command_name == 0) {
            jump_func(assm, current_pointer, assm->size_arr, 1);
            continue;
        }

        if ((command_name != 0) && (command_name >= 3) && (command_name != CALL) && (command_name != JP)) {
            *(assm->arr + assm->size_arr) = command_name;
            if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
            }
            assm->size_arr = assm->size_arr + sizeof(char);
            continue;
        }

        if (command_name == CALL) {
            jump_func(assm, current_pointer, assm->size_arr, 0);
            *(assm->arr + assm->size_arr) = CALL;
            assm->size_arr += (sizeof(char) + sizeof(int));
            continue;
        }

        if (i == (assm->data.text.size - 1)) {
            continue;
        }
    }

    for (int i = 0; i < (assm->size_arr + 1); i++) {
        printf("arr[%d] = %u\n", i, *(unsigned char*)(assm->arr + i));
    }
    printf_lable_array(assm);

    second_bypass(assm);

    for (int i = 0; i < (assm->size_arr + 1); i++) {
        printf("arr[%d] = %u\n", i, *(unsigned char*)(assm->arr + i));
    }

    fwrite(assm->arr, sizeof(char), assm->size_arr + 1, file_b);

    fclose(file_b);
}

void remove_comments(struct Asm* assm) { 
    for (int i = 0; i < assm->data.text.size; i++) {
        char* current_pointer = assm->data.text.strings[i].str; 
        current_pointer = strchr(current_pointer, '#');
        if (current_pointer != nullptr) {
            *current_pointer = '\0';
            assm->data.text.strings[i].len = (int)(current_pointer - assm->data.text.strings[i].str);
        }
    }
}

char* skip_sp(char* str) {
    while (*str == ' ') {
        str++;
    }
    return str;
}

void Asm_dtor(struct Asm* assm) {
    free(assm->arr);
    for (int i = 0; i < 10; i++) {
        free(assm->jump.lable[i].jump_start.jump_start);
    }
    onegin_dtor(&assm->data);
    free(assm->jump.lable);
}

