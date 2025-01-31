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
    int music_len, pattern_len, k = 0, succes = 0;
    while(k < 1){
        read_test_case(input_file, &music, &music_len, &pattern, &pattern_len);
        int* pattern_int_array = (int*)malloc(pattern_len * sizeof(int));
        for(int i = 0; i < pattern_len; i++){
            pattern_int_array[i] = map_to_int(pattern[i]);
        }
        for(int i = 0; i < 12; i++){
            // succes = boyer_moore_horspool(music_len, music, pattern_len, pattern_int_array);
            succes = shift_and(music, music_len, pattern_int_array, pattern_len);
            printf("Suc = %d\n", succes);
            // succes = knuth_morris_pratt(music, music_len, pattern_int_array, pattern_len);
            increase_tune(pattern_int_array, pattern_len);
            if(succes >= 0){
                printf("S %d\n", succes);
                break;
            }
            else if(succes == -2){
                printf("Estouro\n");
                break;
            }
        }
        if(succes == -1){
            printf("N\n");
        }
        // brute_force(music_len, music, pattern_len, pattern_int_array);
        free(pattern_int_array);
        k++;
    }
    
    return 0;
}