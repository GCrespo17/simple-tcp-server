#include "server.h"
#include <cstdlib>
#include <sys/socket.h>
#include <iostream>

int createSocket(int domain, int type, int protocol){
    int socketFileDescriptor{socket(domain, type, protocol)};
    if(socketFileDescriptor<0){
        std::cerr <<"Filed to create Socket...\n";
        exit(EXIT_FAILURE);
    }
    std::cout<<"Socket created successfully...\n";
    return socketFileDescriptor;
}

void bindSocket(int socketFileDescriptor, const struct sockaddr *addr){    
    int bindMySocket{bind(socketFileDescriptor, addr, sizeof(*addr))};
    if(bindMySocket<0){
        std::cerr <<"Binding failed...\n";
        exit(EXIT_FAILURE);    
    }
    std::cout<<"Socket binded successfully...\n";
}

void listenToMessages(int socketFileDescriptor, int backlog, int port){
    int listening = listen(socketFileDescriptor, backlog);
    if(listening<0){
        std::cerr <<"Listening failed...\n";
        exit(EXIT_FAILURE);
    }
    std::cout<<"Listening on Port "<<port<<"...\n";
}

