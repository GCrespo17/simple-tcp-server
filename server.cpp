#include "server.h"
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>

HttpServer::HttpServer():mySocketAddress{}, peerAddress{}, socketFileDescriptor{}, currentConnectionCounter{}{
    mySocketAddress.sin_addr.s_addr = INADDR_ANY;
    mySocketAddress.sin_family = AF_INET;
    mySocketAddress.sin_port = htons(port);
}

HttpServer::~HttpServer(){}


void HttpServer::createSocket(int domain, int type, int protocol){
    int newSocketFileDescriptor{socket(domain, type, protocol)};
    if(newSocketFileDescriptor<0){
        std::cerr <<"Filed to create Socket...\n";
        exit(EXIT_FAILURE);
    }
    std::cout<<"Socket created successfully...\n";
    socketFileDescriptor = newSocketFileDescriptor;
}

void HttpServer::bindSocket(int socketFileDescriptor, const struct sockaddr *addr){    
    int bindMySocket{bind(socketFileDescriptor, addr, sizeof(*addr))};
    if(bindMySocket<0){
        std::cerr <<"Binding failed...\n";
        exit(EXIT_FAILURE);    
    }
    std::cout<<"Socket binded successfully...\n";
}

void HttpServer::listenToMessages(int socketFileDescriptor, int backlog, int port){
    int listening = listen(socketFileDescriptor, backlog);
    if(listening<0){
        std::cerr <<"Listening failed...\n";
        exit(EXIT_FAILURE);
    }
    std::cout<<"Listening on Port "<<port<<"...\n";
}

void HttpServer::acceptConnection(int socketFileDescriptor, struct sockaddr *peerAddress){
    socklen_t sizeOfPeerAddress{sizeof(*peerAddress)};
    int peerFileDescriptor{accept(socketFileDescriptor, peerAddress, &sizeOfPeerAddress)};
    if(peerFileDescriptor < 0){
        std::cerr<<"Failed to connect to peer...\n";
        exit(EXIT_FAILURE);
    }
    peerConnections[currentConnectionCounter]=peerFileDescriptor;
}

void HttpServer::initServer(){
    createSocket(AF_INET, SOCK_STREAM, defaultProtocol);
    bindSocket(socketFileDescriptor, reinterpret_cast<const struct sockaddr *>(&mySocketAddress));
}

void HttpServer::startServer(){
    listenToMessages(socketFileDescriptor, maximumConnections, port);
    acceptConnection(socketFileDescriptor, reinterpret_cast<struct sockaddr *>(&mySocketAddress));
}
