/* This defines types per the build environment
*  There are system differences that I haven't implemented yet. */

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