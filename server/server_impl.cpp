#include "server.h"
#include <fstream>
#include "utils.hpp"
#include <string>
#include <thread>
#include <mutex>

int TCPServer::start()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) 
    {
        perror("Error creating socket");
        return -1;
    }

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr.s_addr = INADDR_ANY;
    servInfo.sin_port = htons(sockPort);
    if (bind(sock, reinterpret_cast<struct sockaddr*>(&servInfo), sizeof(servInfo)) == -1) 
    {
        perror("Bind failed");
        close(sock);
        return -1;
    }

    if (listen(sock, SOMAXCONN) == -1) 
    {
        perror("Listen failed");
        close(sock);
        return -1;
    }
    return 1;
}

void TCPServer::manage_connection(int ClSocket)
{
    int roomIdInternal = 0;
    std::string response;
    while (true)
    {
        try
        {
            char buffer[1024];
            memset(buffer, 0, 1024);
            ssize_t bytesReceived = recv(ClSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) 
            {
                std::string bufdata(buffer, bytesReceived);
                // std::cout << "here is bufdata: " << bufdata;

                if (bufdata.find("hello") != std::string::npos) // connect to room
                {
                    bufdata.erase(0,6);
                    roomIdInternal = std::stoi(bufdata);
                    std::cerr << "CLIENT ON SOCK: " << std::to_string(ClSocket) << " CONNECTED TO ROOM: " << bufdata << "\n";
                    response = "you are connected";
                    if (roomIdInternal == 0)
                    {
                        aint1 += 1;
                    }
                    else if (roomIdInternal == 1)
                    {
                        aint2 += 1;
                    }
                    else aint3 += 1;
                }

                if (bufdata.find("send") != std::string::npos) // connect to room
                {
                    bufdata.erase(0,5);
                    response = "received message";
                }

                send(ClSocket, response.c_str(), strlen(response.c_str()), 0);
            }
        }
        catch (...)
        {
            break;
        }
    }
}

void TCPServer::poll()
{
    while (true)
    {
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientsock = accept(sock, nullptr, nullptr);
        if (clientsock == -1) 
        {
            perror("Accept failed");
            continue;
        }

        threadPool.emplace_back([this, clientsock]() { this->manage_connection(clientsock); });
        std::cout << "thread taken" << std::endl; // debug
    }

    return;
}