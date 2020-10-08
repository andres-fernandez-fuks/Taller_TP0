//
// Created by andres on 7/10/20.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "decodificacion_rc4.h"


void swap(unsigned char* arreglo, unsigned int pos_1, unsigned int pos_2) {
    unsigned char temp = arreglo[pos_1];
    arreglo[pos_1] = arreglo[pos_2];
    arreglo[pos_2] = temp;
}

void rc4_init(unsigned char* arreglo_random, unsigned char* string_clave, unsigned int largo_clave) {
    unsigned int i,j;
    for (i = 0; i < 256; ++i)
        arreglo_random[i] = i;

    for (i = j = 0; i < 256; ++i) {
        j = (j + string_clave[i % largo_clave] + arreglo_random[i]) & 255;
        swap(arreglo_random, i, j);
    }
}

unsigned char rc4_output(unsigned char* arreglo_random) {
    static unsigned int pos_1,pos_2 = 0;
    pos_1 = (pos_1+1) & 255;
    pos_2 = (pos_2+ arreglo_random[pos_1]) & 255;
    swap(arreglo_random,pos_1,pos_2);
    return arreglo_random[(arreglo_random[pos_1]+arreglo_random[pos_2]) & 255];
}

unsigned char* decodificar_rc4(char* input_string, char* clave) {
    size_t largo_input = strlen(input_string);
    size_t largo_clave = strlen(clave);
    char* copia_clave = malloc(largo_clave);
    strncpy(copia_clave,clave,largo_clave);
    unsigned char* output = malloc(largo_input*sizeof(unsigned int));
    char* arreglo_random = malloc(256);
    rc4_init(arreglo_random,copia_clave,largo_clave);

    for (size_t i = 0; i < largo_input; ++i) {
        output[i] = (unsigned char) input_string[i] ^ rc4_output(arreglo_random);
    }
    free(arreglo_random);
    free(copia_clave);
    return output;
}
