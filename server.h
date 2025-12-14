#ifndef H_SERVER
#define H_SERVER

#include <sys/socket.h>
int createSocket(int domain, int type, int protocol);

void bindSocket(int socketFileDecriptor, const struct sockaddr *addr);

void listenToMessages(int socketFileDescriptor, int backlog, int port);
#endif
