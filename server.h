#ifndef H_SERVER
#define H_SERVER

#include <sys/socket.h>
int createSocket(int domain, int type, int protocol);

int bindSocket(int socketFileDecriptor, const struct sockaddr *addr);

int listenToMessages(int socketFileDescriptor, int backlog);

int handleSocketCreation(int domain, int type, int protocol);

void handleBindingSocket(int socketFileDescriptor, struct sockaddr_in *mySocket);

void handleListening(int socketFileDescriptor, int backlog, int port);
#endif
