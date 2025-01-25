#ifndef PATTERN_MATCHING_H
#define PATTERN_MATCHING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int brute_force(int m,  char** music, int t, char** pattern);

char** increase_tune(char** pattern, int len);

int boyer_moore_horspool(int m,  char** music, int t, char** pattern);

#endif