#include "pattern_matching.h"

//Aumenta um semitom em pattern
char** increase_tune(char** pattern, int len){
    char notes[12][3] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    char** new_pattern = (char**)malloc(len * sizeof(char*));
    for(int i = 0 ; i < len; i++){
        new_pattern[i] = (char*)malloc(3);
    }
    for(int i = 0; i < len; i++){
        for(int j = 0; j < 12; j++){
            if(!strcmp(pattern[i], notes[j])) {
                new_pattern[i] = strdup(notes[(j + 1) % 12]);
                break;
            }
        }
    }
    
    free(pattern);
    return new_pattern;
}

//Algoritmo de forca bruta para casamento de padrao
int brute_force(int m,  char** music, int t, char** pattern){
    int j, k;
    for(int i = 0; i <= m - t; i++){
        k = i;
        j = 0;
        while(!strcmp(music[k],pattern[j])){
            j += 1;
            k += 1;
            if(j == t){
                printf("Casamento na posicao %d\n", i);
                return i;
            }
        }
    }
    printf("Padrao nao encontrado\n");
    return -1;
}

int boyer_moore_horspool(int m,  char** music, int t, char** pattern){
    int* d = (int*)malloc(t * sizeof(int));
    for(int i = 0; i < t; i++){
        d[i] = t;
    }
    for(int i = 0; i < t - 1; i++){
       d[i] = t + 1 - i; 
    }
    for(int i = 0; i < t; i++){
        printf("%d ", d[i]);
    }
    int i = t, k, j;
    printf("LOG\n");
    while(i <= m){
        k = i;
        j = t;
        printf("j = %d\nk = %d\n", j , k);
        while(!strcmp(music[k], pattern[j - 1]) && j > 0){
            k -= 1;
            j -= 1;
            printf("i = %d\n", i);
            if(j == 0){
                printf("Casamento na posicao %d\n", k + 1);
                return k + 1;
            }
        }
        printf("d = %d\n", d[t - 1]);
        i += d[t - 1];

    }
    printf("\n");
    return 0;
}