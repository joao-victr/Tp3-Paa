#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pattern_matching.h"

void get_input(int argc, char* argv[], FILE** input_file, int* method);

char** split(char* str);

void read_test_case(FILE* input_file, char*** music, int *m, char*** pattern, int *t);


#endif