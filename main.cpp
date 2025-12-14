#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
    HttpServer server{};
    server.initServer();
    server.startServer();
    return 0;
}

