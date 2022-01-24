//// Copyright 2021, Eric Dee - All rights reserved
//// socket_tcp.c, cache_manager.c, file_manager.c
////
////

#ifndef IO_LIBRAIRES_H
#include "headers/io_libraries.h"
#define IO_LIBRAIRES_H
#endif

#ifndef SOCKET_LIBRARIES_H
#include "headers/socket_libraries.h"
#define SOCKET_LIBRARIES_H
#endif

#include "cache_manager.c"
#include "file_manager.c"

typedef unsigned int socketlengthint; // If errors check here.

FILE* Global_HTMLIndexFile;

FILE* read_file_path(const char* path, char print);
void print_file(FILE* file);
void allow_socket_client(socketint socketFileDescriptor, struct sockaddr_in socketAddressBlock, int socketAddressBlockLength, u_short transport_addres);
void display_cached_block(char* cachedBlock);
char* collect_file(FILE* fileToCollect, void* insert, char* cachedHTMLIndex);
char* collect_file_from_offset(FILE* fileToCollect, char* base_file, int start_point);

char http_protocol_header[] =
                            "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html; charset=UTF-8\r\n\r\n";
#define HTTP_HEADER_LIMITATION sizeof(http_protocol_header)

struct CacheManager StaticCache;
struct FileManager FileManager;

int main()
{
    char production = 'n';

    /* This turns off stdout/printing buffers */
    setbuf(stdout, NULL);

    printf("################\n");
    printf("Base file limitation: %i\n", BASE_FILE_LIMITATION);
    printf("Cache limitation: %i\n", CACHE_LIMITATION);
    printf("Payload limitation: %i\n", PAYLOAD_LIMITATION);
    printf("################\n\n\n\n");

    /* If the build environment is Windows, the Windows socket library initialization step is required. */
    #if defined(_WIN32)
        
        WSADATA winsock_data;
        if (WSAStartup(MAKEWORD(2, 2), &winsock_data)) {
            fprintf(stderr, "Winsock startup failed.\n");
        }
    
    #endif

    Global_HTMLIndexFile = read_file_path("/root/env/internet_server/index.html", 'n');
    if (Global_HTMLIndexFile == NULL) printf("File read_file_path error");

    assemble_cacher(&StaticCache);

    StaticCache.assign_header_by_limitation(BASE_FILE_LIMITATION, HTTP_HEADER_LIMITATION, http_protocol_header, StaticCache.material_cachedHTTPHeader, (any)0);
    StaticCache.assign_response_by_limitation_offset(CACHE_LIMITATION, BASE_FILE_LIMITATION, StaticCache.material_cachedHTTPHeader, StaticCache.built_cachedHTMLIndexResponse, collect_file(Global_HTMLIndexFile, (any)0, StaticCache.material_cachedHTMLIndex));

    /*

        End of initialization settings

    */

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
    u_short transport_address; // Port
    if (production == 'n')
    {
        transport_address = 256;
    }
    else {
        transport_address = 80;
    }

    memset((char*)&socket_address_block.sin_zero, 0, sizeof socket_address_block.sin_zero); // This pads the entire block with bytes.
    socket_address_block.sin_family = address_family;
    socket_address_block.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0 (Let the OS define)
    socket_address_block.sin_port = htons(transport_address);

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

    allow_socket_client(socket_file_descriptor, socket_address_block, socket_address_block_length, transport_address);

    /*
        This is the end of the software process

    */

    printf("This is the end of the socket_tcp.c software process\n");

    return 0;
}

void allow_socket_client(socketint socketFileDescriptor, struct sockaddr_in socketAddressBlock, int socketAddressBlockLength, u_short transportAddress)
{

    char clientIsAllowed = 1;

    printf("Started the allow socket method.\n");

    while (clientIsAllowed == 1)
    {

        printf("This server is looping and waiting for a request on port number %i.\n", transportAddress);

        int client_connection_address = accept(socketFileDescriptor, (struct sockaddr*) &socketAddressBlock, (socketlengthint*) &socketAddressBlockLength);

        if (client_connection_address >= 0)
        {
            printf("A client has made a request!\n");
        }
        else
        {
            perror("The socket experienced a failure during instantiation of the accepted connection address.\n");
            exit(EXIT_FAILURE);
        }

        char request_retainer[CACHE_LIMITATION] = {0};
        read(client_connection_address, request_retainer, CACHE_LIMITATION);
        printf("%s\n", request_retainer);
        send(client_connection_address, StaticCache.built_cachedHTMLIndexResponse, CACHE_LIMITATION, 0);
        printf("Sent the response to the client connection.\n\n\n");
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

----------------------
- write/send structure -
----------------------

Since everything is being built as byte pointers, sizeof is useless. Remember to us the defines:

send(client_connection_address, http_protocol_header, sizeof(http_protocol_header), 0);
-> send(client_connection_address, built_cachedHTMLIndexResponse, CACHE_LIMITATION, 0);

*/