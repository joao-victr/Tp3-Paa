#ifndef PATTERN_MATCHING_H
#define PATTERN_MATCHING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Note{
    char note[3];
    unsigned int bitmask;
} Note;

int brute_force(int m,  char** music, int t, char** pattern);

char** increase_tune(char** pattern, int len);

int boyer_moore_horspool(int m,  char** music, int t, char** pattern);

Note* get_alphabet();

int shift_and(char** music, int music_len, char** pattern, int pattern_len);

#endif