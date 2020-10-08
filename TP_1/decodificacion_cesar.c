//
// Created by andres on 7/10/20.

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "decodificacion_cesar.h"

#define TOTAL_CARACTERES 256
#define OP_CODIFICAR 1

unsigned char* decodificar_cesar(char* input_string, char* offset_string, size_t tipoDeOperacion) {
    int largo_cadena = strlen(input_string);
    int offset = atoi(offset_string);
    unsigned char* output = malloc(largo_cadena);
    for (size_t i = 0; i < largo_cadena; ++i) {
        if (tipoDeOperacion == OP_CODIFICAR)
            output[i] = (input_string[i] + offset)%TOTAL_CARACTERES;
        else
            output[i] = (input_string[i] - offset)%TOTAL_CARACTERES;
    }
    return output;
}

unsigned char* decodificar_vigenere(char* input_string,char* clave, size_t tipoDeOperacion) {
    int largo_input = strlen(input_string);
    int largo_clave = strlen(clave);
    unsigned char* output = malloc(largo_input);
    for (size_t i = 0; i < largo_input; ++i) {
        int pos_clave = i%largo_clave;
        if (tipoDeOperacion == OP_CODIFICAR)
            output[i] = (input_string[i] + clave[pos_clave])%256;
        else
            output[i] = (input_string[i] - clave[pos_clave])%256;
    }
    return output;
}

