#include "input.h"

void get_input(int argc, char* argv[], FILE** input_file, int* method){
    int opt;
    char filepath[50] = "";
    *input_file = fopen(strcat(filepath,argv[1]), "r");
    *method = atoi(argv[2]);
}

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

int read_test_case(FILE* input_file, char*** music, int *m, char*** pattern, int *t){
    char str[50];
    char* eof = 0;
    eof = fgets(str, 20, input_file);
    if(eof == NULL){
        return 1;
    }
    char* token = strtok(str, " ");
    *m = atoi(token);
    token = strtok(NULL, " ");
    *t = atoi(token);

    int len = *m * 4 + 1;
    char* music_line = (char*)malloc(len);
    fgets(music_line, len, input_file);
    char** music_line_split = split(music_line);
    *music = music_line_split;

    len = *t * 3 + 1;
    char* pattern_line = (char*)malloc(len);
    fgets(pattern_line, len, input_file);
    char **pattern_line_split = split(pattern_line);
    *pattern = pattern_line_split;
    return 0;
}

