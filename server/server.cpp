#include "server.h"
#include "iostream"

int main()
{
    TCPServer server{13000};
    if (server.start() == -1)
    {
        return 0;
    }
    else
    {
        server.poll();
        server.stop();
    }
    
    return 0;
}