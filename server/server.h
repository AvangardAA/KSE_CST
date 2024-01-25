#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class TCPServer
{
public:
    TCPServer(int port)
    {
        sockPort = port;
    }

    int start();

    void poll();

    void stop() {close(sock);};

private:
    int sockPort = 0;
    sockaddr_in servInfo;
    sockaddr_in clientAddr{};
    int sock = 0;
    int clientsock = 0;
};