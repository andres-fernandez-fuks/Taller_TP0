//
// Created by andres on 8/10/20.
//

#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void inicializar_hints(struct addrinfo* hints);

int conectarAlSocket(unsigned char* mensaje, char* host_name, char* port_name) {
    struct addrinfo hints;
    struct addrinfo *results, *address;
    int getaddrinfo_ok,socket_fd;
    inicializar_hints(&hints);

    getaddrinfo_ok = getaddrinfo(host_name, port_name, &hints, &results);
    if (!getaddrinfo_ok) {
        fprintf(stderr, "Error en getaddrinfo\n");
        exit(EXIT_FAILURE);
    }

    for (address = results; address != NULL; address = address->ai_next) { // recorro la lista de ips obtenidas en results
        socket_fd = socket(address->ai_family, address->ai_socktype,address->ai_protocol);
        if (socket_fd == -1)
            continue;

        if (connect(socket_fd, address->ai_addr, address->ai_addrlen) != -1)
            break;

        close(socket_fd);
    }

    if (!socket_fd) {
        fprintf(stderr,"Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(results);
    return 0;
}

void inicializar_hints(struct addrinfo* hints) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = 0;
}