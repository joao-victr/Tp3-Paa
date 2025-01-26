#include "pattern_matching.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE* input_file;
    int method;
    get_input(argc, argv, &input_file, &method);
    char **music, **pattern;
    int m, t;

    read_test_case(input_file, &music, &m, &pattern, &t);
    printf("M = %d\nT = %d\n", m, t);
    for(int i = 0; i < m; i++){
        printf("%s ", music[i]);
    }
    printf("\n\n");
    int k = 0;
    // while(k < 12){
    //     for(int i = 0; i < t; i++){
    //         printf("%s ", pattern[i]);
    //     }
    //     printf("\n");
    //     brute_force(m, music, t, pattern);
    //     pattern = increase_tune(pattern, t);
    //     k++;
    // }
    // printf("\n");
    return 0;
}