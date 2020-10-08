#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "decodificacion_cesar.h"
#include "decodificacion_rc4.h"

#define OP_CODIFICAR 1
#define OP_DECODIFICAR 2
#define ERROR_ARGS 1
#define ERROR_STDIN 2

char* obtenerInputString();
int decodificar_cadena(char* input_string, char** argv);
char* copiar_argumento(char* argumento_original);
void imprimir_cadena(unsigned char* cadena_encriptada,size_t largo_cadena);

int main(int argc, char** argv) {
    if ((argc == 5))
        return -ERROR_ARGS;
    char* input_string = obtenerInputString();
    if (!input_string)
        return -ERROR_STDIN;
    return decodificar_cadena(input_string,argv);
}

char* obtenerInputString() {
    printf("Por favor, ingresar el mensaje a enviar: \n");
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
    char* copia_metodo = copiar_argumento(argv[4]);
    char* copia_clave = copiar_argumento(argv[5]);
    puts(copia_metodo);
    puts(copia_clave);
    if (!copia_metodo || !copia_clave)
        return NULL;
    unsigned char* cadena_encriptada = malloc(strlen(input_string));
    if (strcmp(copia_metodo,"cesar") == 0)
        cadena_encriptada = decodificar_cesar(input_string,copia_clave,OP_CODIFICAR);
    else if (strcmp(copia_metodo,"vigenere") == 0)
        cadena_encriptada = decodificar_vigenere(input_string,copia_clave,OP_CODIFICAR);
    else if (strcmp(copia_metodo,"rc4") == 0)
        cadena_encriptada = decodificar_rc4(input_string,copia_clave);
    else
        return -ERROR_ARGS;
    imprimir_cadena(cadena_encriptada,strlen(input_string));
    return 0;

}

char* copiar_argumento(char* argumento_original) {
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