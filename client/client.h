#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

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
    std::string put_del_info(const std::string& filename, int mode); // mode info in implementation enum
    std::string set_directory(const std::string& filename);
    std::string send_hello(int roomname);
    std::string send_msg(const std::string& msg);
    void stop() {close(sock);};

private:
    int sockport = 0;
    const char* servIp = "127.0.0.1";
    sockaddr_in servInfo;
    int sock = 0;
};