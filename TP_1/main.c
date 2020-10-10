//
// Created by andres on 8/10/20.
//

#include <stdio.h>
#include "client_conectarAlSocket.h"
#include "server_bindearAlSocket.h"
#include "aux_cipher.h"

/*
int main(int argc,char** argv) {

    char* port;
    unsigned char mensaje[5] = "Andyy";
    if (argc == 5) {
        port = argv[2];
        bindearAlSocket(port);
    } else {
        char* host = argv[2];
        port = argv[3];
        conectarAlSocket(mensaje,host,port);
    }

    return 0;

}
 */

int main(int argc, char** argv) {
    char* input_string = obtenerInputString();
    printf("Input string: %s\n",input_string);
    if (!input_string)
        return -1;
    return decodificar_cadena(input_string,argv);
}