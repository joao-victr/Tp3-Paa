#include "input.h"

//Faz a leitura dos parametros de entrada
void get_input(int argc, char* argv[], FILE** input_file, int* method){
    int opt;
    char filepath[50] = "";
    *input_file = fopen(strcat(filepath,argv[1]), "r");
    *method = atoi(argv[2]);
}

//Divide a strings em tokens separados por espaço em branco
char** split(char* str){
    if(str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    int i = 0;
    char** str_array = (char**)malloc(strlen(str)* sizeof(char*));
    char* token = strtok(str, " ");
    while(token != NULL){
        str_array[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    return str_array;
}

//Faz a leitura do proximo caso de teste
int read_test_case(FILE* input_file, char*** music, int *m, char*** pattern, int *t, char** music_buffer, char** pattern_buffer){
    char str[50];
    if (fgets(str, 20, input_file) == NULL) return 1;
    sscanf(str, "%d %d", m, t);
    int len = *m * 4 + 1;
    *music_buffer = (char*)malloc(len);
    fgets(*music_buffer, len, input_file);
    *music = split(*music_buffer);
    len = *t * 3 + 1;
    *pattern_buffer = (char*)malloc(len);
    fgets(*pattern_buffer, len, input_file);
    *pattern = split(*pattern_buffer);
    return 0;
}

