#include "input.h"

void get_input(int argc, char* argv[], FILE** input_file, int* method){
    int opt;
    char filepath[50];
    while((opt = getopt(argc, argv, "a:b:")) != -1){
        switch(opt){
            case 'a':
                strcpy(filepath,"");
                *input_file = fopen(strcat(filepath,optarg), "r");
                break;
            case 'b':
            strcpy(filepath,"");
                *method = atoi(optarg);
                break;
            default:
                printf("Uso invalido\n");
        }
    }
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

void read_test_case(FILE* input_file, char*** music, int *m, char*** pattern, int *t){
    char str[10];
    fgets(str, 10, input_file);
    *m = atoi(&str[0]);
    *t = atoi(&str[3]);

    int len = *m * 4 + 1;
    char* music_line = (char*)malloc(len);
    fgets(music_line, len, input_file);
    char** music_line_split = split(music_line);
    *music = music_line_split;

    len = *t * 4 + 1;
    char* pattern_line = (char*)malloc(len);
    fgets(pattern_line, len, input_file);
    char **pattern_line_split = split(pattern_line);
    *pattern = pattern_line_split;
}

