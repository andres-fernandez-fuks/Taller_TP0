#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "cipher.h"

#define CODE_OP 0
#define DECODE_OP 1
#define ERROR_ARGS 1
#define ERROR_STDIN 2
#define ERROR_CIPHER 3

#include "aux_cipher.h"

char* obtenerInputString() {
    //printf("Por favor, ingresar el mensaje a enviar: \n"); Esto no me sirve por un bug de CLion
    char buffer[PATH_MAX];
    size_t contador = 0;
    while (!feof(stdin)) {
        contador += fread(buffer,1,PATH_MAX,stdin);
    }
    if (!contador)
        return NULL;
    char* cadena = malloc(contador+1);
    strncpy(cadena,buffer,contador);
    cadena[contador] = '\0';
    return cadena;
}

int decodificar_cadena(char* input_string, char** argv) {
    int ret = 0;
    char* method_name = obtener_argumento(argv[4]);
    char* key_string = obtener_argumento(argv[5]);
    if (!method_name || !key_string)
        return -ERROR_ARGS;
    cipher_t cipher;
    memset(&cipher,0,sizeof(cipher_t));
    cipherInit(&cipher,method_name);
    size_t input_len = strlen(input_string);
    unsigned char buffer[64] = {0};
    cipherCode(&cipher, (unsigned char*) input_string, input_len, key_string,buffer);
    imprimir_cadena(buffer,strlen(input_string));
    return ret;

}

char* obtener_argumento(char* argumento_original) {
    char* pos_nombre_arg = strrchr(argumento_original,'=');
    if (!pos_nombre_arg) return NULL;
    pos_nombre_arg += 1; // la posicion real es la proxima al "="
    size_t largo_nombre_arg = strlen(argumento_original)-((int)pos_nombre_arg-(int)argumento_original);
    char* argumento = malloc(largo_nombre_arg+1);
    strncpy(argumento,pos_nombre_arg,largo_nombre_arg);
    argumento[largo_nombre_arg] = '\0';
    return argumento;
}

void imprimir_cadena(unsigned char* cadena_encriptada,size_t largo_cadena) {
    for (size_t i = 0; i < largo_cadena; ++i)
        printf("%d",cadena_encriptada[i]);
}

