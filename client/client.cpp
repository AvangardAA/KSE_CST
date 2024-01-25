#include <iostream>
#include "client.h"

enum MsgType
{
    GET,
    LIST,
    PUT,
    DELETE,
    INFO
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
        while (true)
        {
            int command;
            std::cout << "\ninput type of msg: (GET - 0, LIST - 1, PUT - 2, DELETE - 3, INFO - 4): ";
            std::cin >> command;
            std::string fName;

            if (command == MsgType::GET)
            {
                std::cout << "\ninput filename to get with extension (.): "; 
                std::cin >> fName;
                std::string res = client.get(fName);
                if (res == "missing")
                {
                    std::cout << "your file is missing";
                    return 0;
                }
                else
                {
                    std::cout << res << "\n\n";
                }
            }
        }

        client.stop();
    }
    return 0;
}