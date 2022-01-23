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

FILE* Global_page_index;

#define BASE_FILE_LIMITATION 1024
#define STATIC_FILE_COUNT_LIMIT 16
#define CACHE_LIMITATION (BASE_FILE_LIMITATION * STATIC_FILE_COUNT_LIMIT)
#define PAYLOAD_LIMITATION (CACHE_LIMITATION - BASE_FILE_LIMITATION)

void allow_socket_client(socketint socketFileDescriptor, struct sockaddr_in socketAddressBlock, int socketAddressBlockLength, u_short transport_addres);
void print_file(FILE* file);
char* generate_an_array_by_limitation(int limitation);
void assign_header_by_limitation(int ceilingLimitation, int headerLimitation, char* block);
void display_cached_block(char* cachedBlock);

FILE* read_file_path(const char* path)
{

    FILE* index_html = fopen(path, "r");

    if (index_html == NULL)
    {
        perror("File not found!");
    }

    else
    {
        print_file(index_html);
        printf("\n\n\n\n");
    }

    return index_html;
}

void print_file(FILE* file)
{

    rewind(file);

    int _char;
    do
    {
        if (_char == EOF) break;
        _char = getc(file);
        putchar(_char);
    } while (_char != EOF);
    printf("\n");
}

char protocol_header_http[] = 
                            "HTTP/1.1 200 OK\r\n\n"
                            "Content-Type: text/html; charset=UTF-8\r\n\r\n";

int main()
{

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

    Global_page_index = read_file_path("/root/env/internet_server/index.html");
    if (Global_page_index == NULL) printf("File read_file_path error");

    char* staticIndex = generate_an_array_by_limitation(CACHE_LIMITATION);

    int header_limitation = sizeof(protocol_header_http);

    assign_header_by_limitation(CACHE_LIMITATION, header_limitation, staticIndex);
    display_cached_block(staticIndex);

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

        // char request_retainer[CACHE_LIMITATION] = {0};
        // read(client_connection_address, request_retainer, CACHE_LIMITATION);
        // printf("%s\n", request_retainer);
        // write(client_connection_address, initializer, sizeof(initializer));
        // printf("Wrote the response.\n\n\n");
        // close(client_connection_address);
    }
}




char* generate_an_array_by_limitation(int limitation)
{

    char* array = malloc(limitation*sizeof(char));

    for (int iteration = 0; iteration < limitation; iteration++)
    {
        array[iteration] = '1';
    }

    return array;
}

void assign_header_by_limitation(int cacheLimitation, int endOfHeader, char* block)
{

    for (int iteration = 0; iteration < cacheLimitation; iteration++)
    {
        block[iteration] = '0';

        if (iteration < endOfHeader)
        {
            block[iteration] = protocol_header_http[iteration];
        }
    }
}

void display_cached_block(char* cachedBlock)
{

    for (int iteration = 0; iteration < CACHE_LIMITATION; iteration++)
    {
        putchar(cachedBlock[iteration]);
    }
    putchar('\n');
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