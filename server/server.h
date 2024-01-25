#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class TCPServer
{
    TCPServer(int& port)
    {
        sockPort = port;
    }

public:
    void start();

private:
    int sockPort = 0;
    sockaddr_in serverAddr;
    int sock = 0;
};