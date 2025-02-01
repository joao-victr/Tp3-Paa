#include "pattern_matching.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE* input_file, *output_file;
    output_file = fopen("output.txt", "w");
    int method;
    get_input(argc, argv, &input_file, &method);
    char **music, **pattern;
    int music_len, pattern_len, k = 0, succes = 0;
    int eof = 0;
    while(1){
        char *music_line = NULL, *pattern_line = NULL;
        eof = read_test_case(input_file, &music, &music_len, &pattern, &pattern_len, &music_line, &pattern_line);
        if(eof) break;
        int* pattern_int_array = (int*)malloc(pattern_len * sizeof(int));
        for(int i = 0; i < pattern_len; i++){
            pattern_int_array[i] = map_to_int(pattern[i]);
        }
        
        for(int i = 0; i < 12; i++){
            switch(method){
                case 1:
                    succes = brute_force(music_len, music, pattern_len, pattern_int_array);
                    break;
                case 2:
                    succes = knuth_morris_pratt(music, music_len, pattern_int_array, pattern_len);
                    break;
                case 3: 
                    succes = boyer_moore_horspool(music_len, music, pattern_len, pattern_int_array);
                    break;
                case 4:
                    succes = shift_and(music, music_len, pattern_int_array, pattern_len);
                    break;
            }
            increase_tune(pattern_int_array, pattern_len);
            if(succes >= 0){
                fprintf(output_file, "S %d\n", succes);
                break;
            }
        }
        if(succes == -1){
            fprintf(output_file, "N\n");
        }
        free(pattern_int_array);
        free(music_line);
        free(pattern_line);
        free(music);
        free(pattern);
        k++;
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}