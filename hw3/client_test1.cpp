#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

// BASE CODE USED HERE IS TAKEN FROM OUR HW3 DESCRIPTION EXAMPLE, MODIFIED BY ME

void* receiveMessages(void* arg) 
{
    int clientSocket = *((int*)arg);
    char buffer[4096];
    while (true) 
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) 
        {
            std::cerr << "Server disconnected.\n";
            break;
        }
        buffer[bytesReceived] = '\0';
        std::cout << "\n\nMessage from server: " << buffer << std::endl;
    }
    close(clientSocket);
    pthread_exit(nullptr);
}

int main() 
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) 
    {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(8080);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
    {
        std::cerr << "Connection failed.\n";
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected to server.\n";
    pthread_t receiveThread;

    if (pthread_create(&receiveThread, nullptr, receiveMessages, &clientSocket) !=0) 
    {
        std::cerr << "Failed to create receive thread.\n";
        close(clientSocket);
        return 1;
    }

    char message[4096];
    while (true) 
    {
        std::cout << "\nSend message to server (connect <ID> / rejoin <ID> / message itself): ";
        std::cin.getline(message, sizeof(message));
        send(clientSocket, message, strlen(message), 0);
    }
    pthread_cancel(receiveThread);
    close(clientSocket);
    pthread_join(receiveThread, nullptr);
    return 0;
}
