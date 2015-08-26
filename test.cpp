
#include <iostream>
#include "socket.h"

void wait( float seconds )
{ 
    usleep( (int) ( seconds * 1000000.0f ) );
}

int main()
{
    Socket socket;
    int port = 30000;

    if( !socket.open( port ) )
    {
        std::cout << "error: failed to create socket" << std::endl;
        return 1;
    }

    while(true)
    {
        const char data[] = "This is a string of text";
        char destinationIP[] = "127.0.0.1"; // TODO: implement receving IP from cmd line

        bool sent = socket.sendPacket( Address(destinationIP, port), data, sizeof(data) );

        if( !sent )
        {
            std::cout << "error: packet not sent" << std::endl;
        }

        std::cout << "Packet Sent => " << destinationIP << ":" << port << " [" << data << "]" << std::endl;

        while(true)
        {
            Address sender;
            
            unsigned char buffer[512];

            int received_bytes = socket.receivePacket( sender, buffer, sizeof(buffer) );

            if( received_bytes <= 0 )
            {
                break;
            }

            std::cout << "Packet Recv <= " << sender.getInfo() << ":" << sender.getPort() << " [" << buffer << "]" << std::endl;

        }
    
        wait(.25f);    
    }
    
    return 0;
}
