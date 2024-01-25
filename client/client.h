#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class TCPClient
{
    TCPClient(int& port)
    {
        sockport = port;
    }

public:
    int start();

private:
    int sockport = 0;
    const char* servAddr = "127.0.0.1";
    sockaddr_in servInfo;
    int sock = 0;
};