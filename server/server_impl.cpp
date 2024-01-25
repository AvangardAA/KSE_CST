#include "server.h"
#include <fstream>
#include "utils.hpp"
#include <string>

int TCPServer::start()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
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

    socklen_t clientAddrLen = sizeof(clientAddr);
    clientsock = accept(sock, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);
    if (clientsock == -1) 
    {
        perror("Accept failed");
        return -1;
    }

    return 1;
}

void TCPServer::poll()
{
    while (true)
    {
        char buffer[1024];
        memset(buffer, 0, 1024);
        ssize_t bytesReceived = recv(clientsock, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) 
        {
            std::string bufdata(buffer, sizeof(buffer));
            // std::cout << "here is bufdata: " << bufdata;
            std::string response;
            
            if (bufdata.find("txt") != std::string::npos && bufdata.find("put") != std::string::npos)
            {
                bufdata.erase(0,4);
                if (utils::create_file(bufdata) == -1)
                {
                    response = "create failed";
                }
                else response = "create success";
            }

            else if (bufdata.find("txt") != std::string::npos && bufdata.find("delete") != std::string::npos)
            {
                bufdata.erase(0,7);
                if (utils::delete_file(bufdata) == -1)
                {
                    response = "delete failed";
                }
                else response = "delete succeeded";
            }

            else if (bufdata.find("txt") != std::string::npos && bufdata.find("info") != std::string::npos)
            {
                bufdata.erase(0,5);
                response = utils::get_file_info(bufdata);
            }

            else if (bufdata.find("txt") != std::string::npos) 
            {
                response = utils::get_file(bufdata);
            }

            else if (bufdata.find("list") != std::string::npos) 
            {
                response = utils::list_files();
            }

            // std::cout << "file content: " << filecontent;

            send(clientsock, response.c_str(), strlen(response.c_str()), 0);
        }
    }

    return;
}