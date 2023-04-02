#include "asm.h"

int check_command(const char* string) {

        if (strncmp(string, "PUSH", 4) == 0) {
           return PUSH;
        }

        if (strncmp(string, "POP", 2) == 0) {
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

void print_to_bfile(struct Text* text) {
    FILE* file = fopen("b_file.txt", "wb");

    for (int i = 0; i < text->size; i++) {
        int a = check_command(text->strings[i].str);
        fwrite(&a, sizeof(int), 1, file);
        if (a == PUSH) {
            text->strings[i].str = text->strings[i].str + text->strings[i].len_until_sp;
            int number = 0;
            sscanf(text->strings[i].str, "%d", &number);
            fwrite(&number, sizeof(int), 1, file);
        }
    }

    printf("hueston,we have a problem");
    fclose(file);
}

void read_strings(struct Text* text) {
    for (size_t i = 0; i < text->size ; i++ ) {
        char* current_pointer = text->strings[i].str;
        while(isalpha(*current_pointer)) {
            current_pointer++;
        }
            text->strings[i].len_until_sp = (int)(current_pointer - text->strings[i].str);
            printf("onegin->text.strings[i]/len_until_sp = %d\n", text->strings[i].len_until_sp);
        }
}







