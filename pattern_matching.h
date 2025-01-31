#ifndef PATTERN_MATCHING_H
#define PATTERN_MATCHING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Note{
    char note[3];
    unsigned int bitmask;
} Note;

int brute_force(int m,  char** music, int t, int* pattern_int_array);

int boyer_moore_horspool(int music_len, char** music, int pattern_len, int* pattern_int_array);

int shift_and(char** music, int music_len, int* pattern_int_array, int pattern_len);

int knuth_morris_pratt(char** music, int music_len, int* pattern, int pattern_len);

int map_to_int(char* note);

void increase_tune(int* pattern_int_array, int pattern_len);

#endif