#include "asm.h"
#include "assert.h"

void Asm_ctor(struct Asm* assm){
    onegin_ctor(&assm->text, "cpu.txt");

    assm->arr = (int*)calloc(30, sizeof(int));
    //assm->commands = (int*)calloc(assm->text.text.size, sizeof(char)); 
}

char* remove_position_in_func(char* string){

        if (strncmp(string, "PUSH", 4) == 0) {
            return string + 4;
        }

        if (strncmp(string, "POP", 3) == 0) {
            return string + 3;
        }

        if (strncmp(string, "IN", 2) == 0) {
            return string + 2;
        }

        if (strncmp(string, "MUL", 3) == 0) {
            return string + 3;
        }

        if (strncmp(string, "ADD", 3) == 0) {
            return string + 3;
        }

        if  (strncmp(string, "SUB", 3) == 0)  {
            return string + 3;
        }
        if  (strncmp(string, "DIV", 3) == 0)  {
            return string + 3;
        }
        if  (strncmp(string, "OUT", 3) == 0)  {
            return string + 3;
        }
        return string;
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

void print_to_bfile(struct Asm* assm) {
    int a = 0;
    FILE* file_r = fopen("binary.txt", "wb");

    int j = 0;
    remove_comments(assm);

    for (int i = 0; i < assm->text.text.size; i++) {
        if (assm->text.text.strings[i].len == 0) {
            continue;
        }
        char* current_pointer = assm->text.text.strings[i].str;

        current_pointer = skip_sp(current_pointer);

        if (*current_pointer == '\0') {
            a = 0;
            continue;
        }

        a = check_command(current_pointer);
        assm->arr[j] = a;

        current_pointer = remove_position_in_func(current_pointer);


        if (a == PUSH) {
            int number = 0;
            sscanf(current_pointer, "%d", &number);
            j = j + 1;
            assm->arr[j] = number;
        }

        if (i == assm->text.text.size) {
            break;
        }
        j++;
    }
    fwrite(assm->arr, sizeof(int), j, file_r);
    fclose(file_r);
}

void remove_comments(struct Asm* assm){ 
    for(int i = 0; i < assm->text.text.size; i++) {
        char* current_pointer = assm->text.text.strings[i].str; 
        current_pointer = strchr(current_pointer, '#');
        if (current_pointer != nullptr) {
            *current_pointer = '\0';
            assm->text.text.strings[i].len = (int)(current_pointer - assm->text.text.strings[i].str);
        }
    }
}

char* skip_sp(char* str){
    while (*str == ' ') {
        str++;
    }
    return str;
}


void Asm_dtor(struct Asm* assm) {
    free(assm->arr);
    onegin_dtor(&assm->text);
}





