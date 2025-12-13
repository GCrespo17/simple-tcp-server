#include "server.h"
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <sys/socket.h>
#include <iostream>

int createSocket(int domain, int type, int protocol){
    int socketFileDescriptor{socket(domain, type, protocol)};
    if(socketFileDescriptor<0){
        throw std::runtime_error("Socket creation failed");
    }
    return socketFileDescriptor;
}

int handleSocketCreation(int domain, int type, int protocol){
    try{
        int socketFileDescriptor{createSocket(domain, type, protocol)};
        std::cout<<"Socket created successfully\n";
        return socketFileDescriptor;
    }catch(const std::exception &e){
        throw;
    }
    return -1;
}

int bindSocket(int socketFileDescriptor, const struct sockaddr *addr){    
    int bindMySocket{bind(socketFileDescriptor, addr, sizeof(*addr))};
    if(bindMySocket<0){
        throw std::runtime_error("Failed to bind the socket");
    }
    return bindMySocket;
}

void handleBindingSocket(int socketFileDescriptor, struct sockaddr_in *mySocket){
    try{
        struct sockaddr *convertedSocket = reinterpret_cast<struct sockaddr *>(mySocket);
        int bindMySocket = bindSocket(socketFileDescriptor, convertedSocket);
        std::cout<<"Socket binded successfully\n";
    }catch(const std::exception &e){
        throw;
    }
}

int listenToMessages(int socketFileDescriptor, int backlog){
    int listening = listen(socketFileDescriptor, backlog);
    if(listening<0){
        throw std::runtime_error("Failed to start listening to messages");
    }
    return listening;
}

void handleListening(int socketFileDescriptor, int backlog, int port){
    try{
        int listening = listenToMessages(socketFileDescriptor, backlog);
        std::cout<<"Listening on port "<<port<<"...\n";
    }catch(const std::exception &e){
        throw;
    }
}
