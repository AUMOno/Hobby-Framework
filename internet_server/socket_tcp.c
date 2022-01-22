//// Copyright 2021, Eric Dee - All rights reserved
//// socket_tcp.c
////
////

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Replace this with the printf function I rewrote.
typedef unsigned int socketlengthint; // If errors check here.

/* This Checks the OS, then defines types/delegates per their specification
*  There are differences between the systems that I haven't coded yet. */

#if defined (__unix__)
    typedef int socketint;
    #include <sys/socket.h>
    #include <unistd.h>
    #include <netinet/in.h>

#elif defined(_WIN32)
    typedef unsigned int socketint;
    #include <winsock.h>
    #include <winsock2.h>

#endif

#define BUFFER_LIMITATION 65536

void allow_socket_client(socketint socketFileDescriptor, struct sockaddr_in socketAddressBlock, int socketAddressBlockLength, u_short transport_addres);

int main()
{
    /* This turns off stdout/printing buffers */
    setbuf(stdout, NULL);

    #if defined(_WIN32)
    
        /* If the build environment is Windows, the Windows socket library initialization step is required. */
    
        WSADATA winsock_data;
        if (WSAStartup(MAKEWORD(2, 2), &winsock_data)) {
            fprintf(stderr, "Winsock startup failed.\n");
        }
    
    #endif

    int address_family = AF_INET;
    int type = SOCK_STREAM;
    int protocol = 0;

    socketint socket_file_descriptor = socket(address_family, type, protocol);
    
    if(socket_file_descriptor >= 0)
    {
        int socket_result = setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
        if (socket_result < 0)
        {
            printf("The socket could not be set up for reuse.\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("The socket file descriptor was setup successfully.\n");
        }
    } else
    {
        perror("The socket file descriptor setting failed.\n");
        return 0;
    }

    struct sockaddr_in socket_address_block;
    int socket_address_block_length = sizeof(socket_address_block);
    u_short transport_addres = 256; // Port

    memset((char*)&socket_address_block.sin_zero, 0, sizeof socket_address_block.sin_zero); // This pads the remainder of the block with bytes.
    socket_address_block.sin_family = address_family;
    socket_address_block.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0 (Let the OS define)
    socket_address_block.sin_port = htons(transport_addres);

    int binding_result = bind(socket_file_descriptor, (struct sockaddr*) &socket_address_block, sizeof(socket_address_block));

    if (binding_result >= 0)
    {
        printf("The server bound successfully.\n");
    }
    else {
        perror("The binding failed.");
        exit(EXIT_FAILURE);
    }

    int listening_result = listen(socket_file_descriptor, 16);

    if (listening_result >= 0)
    {
        printf("The server began listening.\n");
    }
    else
    {
        perror("The server could not listen.\n");
        exit(EXIT_FAILURE);
    }

    /*
        This is the end of the setup

    */

    allow_socket_client(socket_file_descriptor, socket_address_block, socket_address_block_length, transport_addres);

    printf("This is the end of the socket_tcp.c software process\n");

    return 0;
}

void allow_socket_client(socketint socketFileDescriptor, struct sockaddr_in socketAddressBlock, int socketAddressBlockLength, u_short transport_addres)
{
    char client_is_allowed = 1;

    printf("Started the allow socket method.\n");

    while (client_is_allowed == 1)
    {

        printf("This server is looping and waiting for a request on port number %i.\n", transport_addres);

        int client_connection_address = accept(socketFileDescriptor, (struct sockaddr*) &socketAddressBlock, (socketlengthint*) &socketAddressBlockLength);

        if (client_connection_address >= 0)
        {
            printf("A client has made a request!");
        }
        else
        {
            perror("The socket experienced a failure during instantiation of the accepted connection address.");
            exit(EXIT_FAILURE);
        }

        char request_retainer[BUFFER_LIMITATION] = {0};
        read(client_connection_address, request_retainer, BUFFER_LIMITATION);
        printf("%s\n", request_retainer);
        char initializer[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<!DOCTYPE html>\r\n"
        "<html><head><title>World Wide Web</title>\r\n"
        "<p>Hello internet</p></html>\r\n";
        write(client_connection_address, initializer, sizeof(initializer));
        printf("Wrote the response.\n\n\n");
        close(client_connection_address);
    }
}




/* Notes:

-------------
- socklen_t -
-------------

socklen_t = unsigned int on unix

----------------------
- sockaddr structure -
----------------------

struct sockaddr_in 
{ 
    __uint8_t         sin_len; 
    sa_family_t       sin_family; 
    in_port_t         sin_port; 
    struct in_addr    sin_addr; 
    char              sin_zero[8]; 
};

*/