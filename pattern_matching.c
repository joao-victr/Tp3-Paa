#include "pattern_matching.h"
#include <stdint.h>

//Mapeia a nota passada como parametro para um numero inteiro
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

//Sobe o tom do padrao em um semitom
void increase_tune(int* pattern_int_array, int pattern_len){
    for(int i = 0; i < pattern_len; i++){
        pattern_int_array[i] = (pattern_int_array[i] + 1) % 12;
    }
}

//Algoritmo forca bruta
int brute_force(int music_len,  char** music, int pattern_len, int* pattern_int_array){
    int j, k;
    for(int i = 0; i <= music_len - pattern_len; i++){
        k = i;
        j = 0;
        while(map_to_int(music[k]) == pattern_int_array[j]){
            j += 1;
            k += 1;
            if(j == pattern_len){
                return i;
            }
        }
    }
    return -1;
}

//Computa a tabela de deslocamentos do BMH
void preprocess_shift_table(int* pattern, int pattern_len, int* shift_table) {
    for (int i = 0; i < 12; i++) {
        shift_table[i] = pattern_len;
    }
    for (int i = 0; i < pattern_len - 1; i++) {
        shift_table[pattern[i]] = pattern_len - 1 - i;
    }
}

//Algoritmo Boyer-Moore-Horspool
int boyer_moore_horspool(int music_len, char** music, int pattern_len, int* pattern_int_array){
    int shift_table[12];
    preprocess_shift_table(pattern_int_array, pattern_len, shift_table);
    int i = 0;
    while (i <= music_len - pattern_len){
        int j = pattern_len - 1;
        
        while(j >= 0 && map_to_int(music[i + j]) == pattern_int_array[j]){
            j--;
        }
        if(j < 0){
            return i;
        }
        i += shift_table[map_to_int(music[i + pattern_len - 1])];
    }
    return -1;
}

//Algoritmo Shift-And
int shift_and(char** music, int music_len, int* pattern_int_array, int pattern_len){
    if(!music_len || !pattern_len) return -1;
    int num_blocks = (pattern_len + 63) / 64;
    uint64_t** table = (uint64_t**)malloc(12 * sizeof(uint64_t*));
    for(int i = 0; i < 12; i++){
        table[i] = (uint64_t*)calloc(num_blocks, sizeof(uint64_t));
    }
    uint64_t* R = (uint64_t*)calloc(num_blocks + 1, sizeof(uint64_t));
    int block, offset;
    for(int i = 0; i < pattern_len; i++){
        block = i / 64;
        offset = i % 64;
        table[pattern_int_array[i]][block] |= (1ULL << offset);
    }
    unsigned long carry;
    for(int i = 0; i < music_len; i++){
        int note_index = map_to_int(music[i]);
        carry = 1ULL;
        for(int j = 0; j < num_blocks; j++){
            R[j] = (R[j] << 1);
            if(j == num_blocks - 1) R[j] |= 1ULL;
            carry = (R[j + 1] >> 63);
            R[j] = (R[j] | carry) & table[note_index][j];
        }
        int last_block = (pattern_len - 1) / 64;
        int last_bit = (pattern_len - 1) % 64;
        if(R[last_block] & (1ULL << last_bit)){
            for(int i = 0; i < 12; i++){
                free(table[i]);
            }
            free(table);
            free(R);
            return i - pattern_len + 1;
        }
    }
    for(int i = 0; i < 12; i++){
       free(table[i]);
    }
    free(table);
    free(R);
    return -1;
}

//Computa o array de prefixos do KMP
void get_prefix_array(int* pattern_int_array, int pattern_len, int* prefix_array){
    int length = 0;
    prefix_array[0] = 0;
    int i = 1;
    while(i < pattern_len){
        if(pattern_int_array[i] == pattern_int_array[length]){
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

//Algoritmo Knuth-Morris-Pratt
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
            free(prefix_array);
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
