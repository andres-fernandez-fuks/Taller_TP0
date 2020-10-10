//
// Created by andres on 10/10/20.
//

#ifndef TP_1_AUX_CIPHER_H
#define TP_1_AUX_CIPHER_H

char* obtenerInputString();
int decodificar_cadena(char* input_string, char** argv);
char* obtener_argumento(char* argumento_original);
void imprimir_cadena(unsigned char* cadena_encriptada,size_t largo_cadena);
char* definirEncriptacionDeCadena(char* input_string,char* nombre_metodo,char* clave);

#endif //TP_1_AUX_CIPHER_H
