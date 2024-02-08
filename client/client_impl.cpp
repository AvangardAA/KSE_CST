#include "client.h"
#include <fstream>

enum SendMode
{
    PUT,
    DELETE,
    INFO
};

int TCPClient::start()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) 
    {
        perror("Error creating socket");
        return -1;
    }

    servInfo.sin_family = AF_INET;
    servInfo.sin_port = htons(sockport);
    inet_pton(AF_INET, servIp, &(servInfo.sin_addr));
    if (connect(sock, reinterpret_cast<struct sockaddr*>(&servInfo), sizeof(servInfo)) == -1) 
    {
        perror("Connect failed");
        close(sock);
        return -1;
    }

    return 1;
}

std::string TCPClient::get(const std::string& filename)
{
    send(sock, filename.c_str(), strlen(filename.c_str()), 0);
    char buffer[1024];
    memset(buffer, 0, 1024);
    ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0)
    {
        return std::string(buffer, sizeof(buffer));
    }
    else return "something went wrong";
}

std::string TCPClient::set_directory(const std::string& filename)
{
    send(sock, filename.c_str(), strlen(filename.c_str()), 0);
    char buffer[1024];
    memset(buffer, 0, 1024);
    ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0)
    {
        return std::string(buffer, sizeof(buffer));
    }
    else return "something went wrong";
}

std::string TCPClient::list()
{
    std::string dummyMsg = "list";
    send(sock, dummyMsg.c_str(), strlen(dummyMsg.c_str()), 0);
    char buffer[1024];
    memset(buffer, 0, 1024);
    ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0)
    {
        return std::string(buffer, sizeof(buffer));
    }
    else return "something went wrong";
}

std::string TCPClient::put_del_info(const std::string& filename, int mode)
{
    std::string dummyMsg = "";

    if (mode == SendMode::PUT)
    {
        dummyMsg += "put";
    }
    else if (mode == SendMode::DELETE)
    {
        dummyMsg += "delete";
    }
    else if (mode == SendMode::INFO)
    {
        dummyMsg += "info";
    }

    dummyMsg += " " + filename;

    send(sock, dummyMsg.c_str(), strlen(dummyMsg.c_str()), 0);
    char buffer[1024];
    memset(buffer, 0, 1024);
    ssize_t bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0)
    {
        return std::string(buffer, sizeof(buffer));
    }
    else return "something went wrong";
}