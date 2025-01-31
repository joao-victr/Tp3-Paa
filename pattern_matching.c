#include "pattern_matching.h"
#include <stdint.h>


int map_to_int(char* note){
        if(!strcmp(note, "A")) return 0;
        else if(!strcmp(note, "A#") || !strcmp(note, "Bb")) return 1;
        else if(!strcmp(note, "B") || !strcmp(note, "Cb")) return 2;
        else if(!strcmp(note, "B#") || !strcmp(note, "C")) return 3;
        else if(!strcmp(note, "C#") || !strcmp(note, "Db")) return 4;
        else if(!strcmp(note, "D")) return 5;
        else if(!strcmp(note, "D#") || !strcmp(note, "Eb")) return 6;
        else if(!strcmp(note, "E") || !strcmp(note, "Fb")) return 7;
        else if(!strcmp(note, "E#") || !strcmp(note, "F")) return 8;
        else if(!strcmp(note, "F#") || !strcmp(note, "Gb")) return 9;
        else if(!strcmp(note, "G")) return 10;
        else if(!strcmp(note, "G#") || !strcmp(note, "Ab")) return 11;
}

void increase_tune(int* pattern_int_array, int pattern_len){
    for(int i = 0; i < pattern_len; i++){
        pattern_int_array[i] = (pattern_int_array[i] + 1) % 12;
    }
}

//Algoritmo de forca bruta para casamento de padrao
int brute_force(int m,  char** music, int t, int* pattern_int_array){
    int j, k, distance;
    for(int i = 0; i <= m - t; i++){
        k = i;
        j = 0;
        int distance = (map_to_int(music[i]) - pattern_int_array[0] + 12) % 12;
        while((map_to_int(music[k]) - pattern_int_array[j] + 12) % 12 == distance){
            j += 1;
            k += 1;
            if(j == t){
                printf("S %d\n", i);
                return i;
            }
        }
    }
    printf("N\n");
    return -1;
}

void preprocess_shift_table(int* pattern, int pattern_len, int* shift_table) {
    for (int i = 0; i < 12; i++) {
        shift_table[i] = pattern_len;
    }
    for (int i = 0; i < pattern_len - 1; i++) {
        shift_table[pattern[i]] = pattern_len - 1 - i;
    }
}

int boyer_moore_horspool(int music_len, char** music, int pattern_len, int* pattern_int_array) {
    int shift_table[12];
    preprocess_shift_table(pattern_int_array, pattern_len, shift_table);
    int i = 0;
    while (i <= music_len - pattern_len) {
        int j = pattern_len - 1;
        
        while (j >= 0 && map_to_int(music[i + j]) == pattern_int_array[j]) {
            j--;
        }
        if (j < 0) {
            return i;
        }
        i += shift_table[map_to_int(music[i + pattern_len - 1])];
    }
    return -1;
}

int shift_and(char** music, int music_len, int* pattern_int_array, int pattern_len) {
    int num_blocks = (pattern_len + 1) / 64, counter = 0, k = 0;
    unsigned long long table[12][num_blocks];
    unsigned long long R[num_blocks];
    memset(table, 0, sizeof(table));
    memset(R, 0, sizeof(R));

    int block, offset;
    for(int i = 0; i < pattern_len; i++){
        block = i / 64;
        offset = i % 64;
        table[pattern_int_array[i]][block] |= (1ULL << offset);
    }

    for(int i = 0; i < music_len; i++){
        int char_index = pattern_int_array[i];
        uint64_t carry = 1;
        for (int j = 0; j < num_blocks; j++) {
            unsigned long long prev_carry = carry;
            carry = (R[i] >> 63) & 1ULL;
            R[i] = ((R[i] << 1) | prev_carry) & table[char_index][i];
        }
        if (R[(pattern_len - 1) / 64] & (1ULL << ((pattern_len - 1) % 64))) {
            printf("pat_len: %d\ni: %d\n", pattern_len, i);
            return i - pattern_len + 1;  // Retorna posição inicial do casamento
        }
    }
    return -1;
}

void get_prefix_array(int* pattern_int_array, int pattern_len, int* prefix_array){
    int length = 0;
    prefix_array[0] = 0;
    int i = 1;
    while (i < pattern_len){
        if (pattern_int_array[i] == pattern_int_array[length]){
            length++;
            prefix_array[i] = length;
            i++;
        }else{
            if(length != 0){
                length = prefix_array[length - 1];
            }else{
                prefix_array[i] = 0;
                i++;
            }
        }
    }
}


int knuth_morris_pratt(char** music, int music_len, int* pattern_int_array, int pattern_len){
    int* prefix_array = (int*)malloc(pattern_len * sizeof(int));
    get_prefix_array(pattern_int_array, pattern_len, prefix_array);
    int i = 0;
    int j = 0;
    while(i < music_len){
        if(pattern_int_array[j] == map_to_int(music[i])){
            i++;
            j++;
        }
        if(j == pattern_len){
            return i - j;
        }else if(i < music_len && pattern_int_array[j] != map_to_int(music[i])){
            if (j != 0){
                j = prefix_array[j - 1];
            }else{
                i++;
            }
        }
    }
    free(prefix_array);
    return -1;
}
