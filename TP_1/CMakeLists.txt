cmake_minimum_required(VERSION 3.17)
project(TP_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(TP_1 aux_cipher.c decodificacion.c decodificacion.h client_conectarAlSocket.c client_conectarAlSocket.h main.c server_bindearAlSocket.h server_bindearAlSocket.c cipher.c cipher.h aux_cipher.h)