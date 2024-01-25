#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class TCPClient
{
public:
    TCPClient(int port)
    {
        sockport = port;
    }

    int start();
    std::string get(const std::string& filename);
    std::string list();

    void stop() {close(sock);};

private:
    int sockport = 0;
    const char* servIp = "127.0.0.1";
    sockaddr_in servInfo;
    int sock = 0;
};