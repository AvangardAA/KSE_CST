#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <thread>
#include <set>

class TCPServer
{
public:
    TCPServer(int port)
    {
        sockPort = port;
    }

    int start();

    void poll();

    void manage_connection(int ClSocket);

    void stop() {close(sock);};

private:
    int sockPort = 0;
    std::set<std::string> usedDirs;
    sockaddr_in servInfo;
    sockaddr_in clientAddr{};
    int sock = 0;
    std::vector<std::thread> threadPool;
};