#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <map>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <ctime>

// BASE CODE USED HERE IS TAKEN FROM OUR HW3 DESCRIPTION EXAMPLE, MODIFIED WITH FEAUTURES BY ME

std::map<int, std::vector<int>> rooms;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcastMessage(const char* message, int senderSocket, int roomID) 
{
    pthread_mutex_lock(&mutex);
    for (int clientSocket : rooms[roomID]) 
    {
        if (clientSocket != senderSocket) 
        {
            send(clientSocket, message, strlen(message), 0);
        }   
    }
    pthread_mutex_unlock(&mutex);
}

void* handleClient(void* arg) 
{
    int clientSocket = *((int*)arg);
    char buffer[4096];
    int roomID = -1; 
    std::cout << "Client (SOCK NUM): " << clientSocket << " connected\n";
    while (true) 
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) 
        {
            pthread_mutex_lock(&mutex);
            auto it = std::find(rooms[roomID].begin(), rooms[roomID].end(), clientSocket);
            if (it != rooms[roomID].end()) 
            {
                rooms[roomID].erase(it);
            }
            pthread_mutex_unlock(&mutex);
            std::cout << "Client (SOCK NUM): " << clientSocket << " disconnected\n";
            close(clientSocket);
            pthread_exit(nullptr);
        }

        buffer[bytesReceived] = '\0';
        std::string bufdata(buffer, bytesReceived);

        if (bufdata.find("connect") != std::string::npos) 
        {
            bufdata.erase(0, 8);
            roomID = std::stoi(bufdata); 
            pthread_mutex_lock(&mutex);
            rooms[roomID].push_back(clientSocket);
            pthread_mutex_unlock(&mutex);
            std::cout << "Client (SOCK NUM): " << clientSocket << " joined room with num: " << roomID << std::endl;
        } 

        else if (bufdata.find("rejoin") != std::string::npos) 
        {
            bufdata.erase(0, 7);
            int newRoomID = std::stoi(bufdata);
            pthread_mutex_lock(&mutex);
            auto it = std::find(rooms[roomID].begin(), rooms[roomID].end(), clientSocket);
            if (it != rooms[roomID].end()) 
            {
                rooms[roomID].erase(it);
            }
            rooms[newRoomID].push_back(clientSocket);
            pthread_mutex_unlock(&mutex);
            roomID = newRoomID;
            std::cout << "Client (SOCK NUM): " << clientSocket << " rejoined room num: " << roomID << std::endl;
        } 

        else 
        {
            std::cout << "Client (SOCK NUM): " << clientSocket << " sent message: " << buffer << std::endl;
            broadcastMessage(buffer, clientSocket, roomID);
        }
    }

    close(clientSocket);
    pthread_exit(nullptr);
}


int main() 
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) 
    {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
    {
        std::cerr << "Bind failed\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == -1) 
    {
        std::cerr << "Listen failed\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on port 8080...\n";
    while (true) 
    {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr,
        &clientAddrLen);

        if (clientSocket == -1) 
        {
            std::cerr << "Accept failed\n";
            close(serverSocket);
            return 1;
        }

        pthread_t thread;
        if (pthread_create(&thread, nullptr, handleClient, &clientSocket) != 0) 
        {
            std::cerr << "Failed to create thread\n";
            close(clientSocket);
        }
        pthread_detach(thread);
    }

    close(serverSocket);
    return 0;
}