#include <iostream>
#include "client.h"

enum MsgType
{
    GET,
    LIST,
    PUT,
    DELETE,
    INFO,
    SET_DIR
};

int main() 
{
    TCPClient client{13000};    
    if (client.start() == -1)
    {
        return 0;
    }
    else
    {
        int roomID;
        std::cout << "\nHello, type room ID to connect (0-2): ";
        std::cin >> roomID;
        client.send_hello(roomID);

        while (true)
        {
            std::string msg;
            std::cout << "\ninput msg to send to chat: ";
            std::cin >> msg;
            std::cout << client.send_msg(msg) << "\n";
        }

        client.stop();
    }
    return 0;
}