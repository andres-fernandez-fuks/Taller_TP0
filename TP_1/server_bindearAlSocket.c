//
// Created by andres on 8/10/20.
//

#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void inicializar_hints_server(struct addrinfo* hints);

int bindearAlSocket(char* port_name) {
    struct addrinfo hints;
    struct addrinfo *results, *address;
    int socket_fd, s,acceptance_socket,valread;
    char buffer[1024] = {0};
    inicializar_hints_server(&hints);
    char *hello = "Hello from server";


    s = getaddrinfo(NULL, port_name, &hints, &results);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (address = results; address != NULL; address = address->ai_next) { // recorro la lista de ips obtenidas en results
        socket_fd = socket(address->ai_family, address->ai_socktype,0);
        if (socket_fd == -1)
            continue;

        if (bind(socket_fd, address->ai_addr, address->ai_addrlen) == 0)
            printf("Bindeado!\n");
            break;

        close(socket_fd);
    }

    if (!address) {       // no se puedo conectar
        fprintf(stderr, "Error en el bind\n");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_fd,1) < 0) {
        fprintf(stderr,"Error en el listen\n");
        exit(EXIT_FAILURE);
    }

    if ((acceptance_socket = accept(socket_fd, (struct sockaddr *)&address->ai_addr,
            (socklen_t*)&address->ai_addrlen)) <0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( acceptance_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(acceptance_socket , hello , strlen(hello) , 0 );
    return 0;

    freeaddrinfo(results);           /* No longer needed */

}

void inicializar_hints_server(struct addrinfo* hints) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
    hints->ai_protocol = 0;
}