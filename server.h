#ifndef H_SERVER
#define H_SERVER

#include <sys/socket.h>
#include <netinet/in.h>
#include <array>

class HttpServer{
    private:
        struct sockaddr_in mySocketAddress;
        struct sockaddr_in peerAddress;
        int socketFileDescriptor;
        int currentConnectionCounter;
 
    public:
        static constexpr int maximumConnections{50};
        static constexpr int port{8080};
        static constexpr int defaultProtocol{0};

    private:
        std::array<int, maximumConnections> peerConnections;
        void createSocket(int domain, int type, int protocol);
        void bindSocket(int socketFileDecriptor, const struct sockaddr *addr);
        void listenToMessages(int socketFileDescriptor, int backlog, int port);
        void acceptConnection(int socketFileDescriptor,struct sockaddr *addr);

    public:
        HttpServer();
        ~HttpServer();
        void initServer();
        void startServer();

              
};

#endif
