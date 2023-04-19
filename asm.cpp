#include "asm.h"
#include "assert.h"

void Asm_ctor(struct Asm* assm){
    onegin_ctor(&assm->data, "cpu.txt");

    assm->arr = (char*)calloc(100, sizeof(int)); // поменять
    assm->sign = ASMSIGN; 

}
char* remove_position_in_func(struct Asm* assm, char* current_pointer, int a) {
    if (a = PUSH) {
        return current_pointer = current_pointer + assm->command_arr[0];
    }

    if (a = IN) {
        return current_pointer = current_pointer + assm->command_arr[1];
    }

    else return current_pointer = current_pointer + assm->command_arr[2];
}

int check_command(char* string){

        if (strncmp(string, "PUSH", 4) == 0) {
            return PUSH;
        }

        if (strncmp(string, "POP", 3) == 0) {
            return POP;
        }

        if (strncmp(string, "IN", 2) == 0) {
            return IN;
        }

        if (strncmp(string, "MUL", 3) == 0) {
            return MUL;
        }

        if (strncmp(string, "ADD", 3) == 0) {
            return ADD;
        }

        if  (strncmp(string, "SUB", 3) == 0)  {
            return SUB;
        }
        if  (strncmp(string, "DIV", 3) == 0)  {
            return DIV;
        }
        if  (strncmp(string, "OUT", 3) == 0)  {
            return OUT;
        }
        return UNKNOWN;
}

void JUMP_func(struct Asm* assm, char* pointer) {
    char* current_pointer = pointer;
    int   lable_len = 0;
    current_pointer++;

    if (*current_pointer != ':') {
        printf("you are so fucking stupid for coding"); 
    }

    current_pointer = skip_sp(current_pointer);

    while ((*current_pointer != '\0') || (*current_pointer != '#')) {
        current_pointer++;
        lable_len++;
    }

    current_pointer = current_pointer - lable_len;

    assm->lable = (char*)calloc(lable_len, sizeof(char));

    for (int i = 0; i < lable_len; i++) {
        assm->lable[i] = *current_pointer;
        current_pointer++;
    } 

    // есть мысль сначал длину метки положить
}

// не получается если метка до джампа
void print_to_bfile(struct Asm* assm) {
    int command_name = 0;
    FILE* file_b = fopen("binary.txt", "wb");
    int ip = 1;
    assm->arr[0] = assm->sign; // тут не оч уверена

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

                *(assm->arr + ip) = 129;
                ip++;
                *(assm->arr + ip) = 1;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                ip++;
                continue;
            }

            if (strncmp(current_pointer, "RBX", 3) == 0){

                *(assm->arr + ip) = 129;
                ip++;
                *(assm->arr + ip) = 2;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                ip++;
                continue;
            }

            if (strncmp(current_pointer, "RCX", 3) == 0){

                *(assm->arr + ip) = 129;
                ip++;
                *(assm->arr + ip) = 3;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                ip++;
                continue;
            }

            if (strncmp(current_pointer, "RDX", 3) == 0){

                *(assm->arr + ip) = 129;
                ip++;
                *(assm->arr + ip) = 4;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                ip++;
                continue;
            }

            else {
            int number = 0;
            sscanf(current_pointer, "%d", &number);

            *(assm->arr + ip) = 1;

            ip++;

            *(assm->arr + ip) = number;


            if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                continue;
            }
            ip++;
            continue;
            }
        }

        if (command_name == POP) {

            current_pointer = skip_sp(current_pointer);

            if (strncmp(current_pointer, "RAX", 3) == 0) {

                *(assm->arr + ip) = 130;
                ip++;
                *(assm->arr + ip) = 1;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                ip++;
                continue;
            }

            if (strncmp(current_pointer, "RBX", 3) == 0){

                *(assm->arr + ip) = 130;
                ip++;
                *(assm->arr + ip) = 2;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    printf("skdjksjdks");
                    continue;
                }
                ip++;
                continue;
            }

            if (strncmp(current_pointer, "RCX", 3) == 0) {

                *(assm->arr + ip) = 130;
                ip++;
                *(assm->arr + ip) = 3;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                ip++;
                continue;
            }

            if (strncmp(current_pointer, "RDX", 3) == 0) {

                *(assm->arr + ip) = 130;
                ip++;
                *(assm->arr + ip) = 4;

                if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                    continue;
                }
                ip++;
                continue;
            }

            else {
            *(assm->arr + ip) = 2;
            if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
                continue;
            }
            ip++;
            continue;
            }
        }

        else {
            *(assm->arr + ip) = command_name;
        }

    if ((i == (assm->data.text.size - 1)) || (assm->data.text.size == 1)) {
        continue;
    }

    ip++;
    }

    printf("ip = %d\n", ip);

    for (int i = 0; i < ip + 1;i++ ) {
        printf("arr[%d] = %hhu\n", i, *(assm->arr + i));
    }

    fwrite(assm->arr, sizeof(int), ip, file_b);
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
    onegin_dtor(&assm->data);
}

