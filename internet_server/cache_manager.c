//// Copyright 2021, Eric Dee - All rights reserved
//// socket_tcp.c, cacher.c
////
////

#ifndef CACHE_MANAGER_H
#include "headers/cache_manager.h"
#define CACHE_MANAGER_H
#endif

/*
* To do: This needs to use arrays. Starting to need a header file too.
*/

struct CacheManager {
    void(*reassemble_this)();
    char* material_cachedHTTPHeader;
    char* material_cachedHTMLIndex;
    char* built_cachedHTMLIndexResponse;
    void(*assign_header_by_limitation)();
    void(*assign_response_by_limitation_offset)();
};

void assemble_cacher(struct CacheManager* delegate)
{
    
    delegate->reassemble_this = assemble_cacher;
    // Fields:
    delegate->material_cachedHTTPHeader = generate_an_array_by_limitation(BASE_FILE_LIMITATION, (any)0);
    delegate->material_cachedHTMLIndex = generate_an_array_by_limitation(CACHE_LIMITATION, (any)0);
    delegate->built_cachedHTMLIndexResponse = generate_an_array_by_limitation(CACHE_LIMITATION, (any)0);
    // Methods:
    delegate->assign_header_by_limitation = assign_header_by_limitation;
    delegate->assign_response_by_limitation_offset = assign_response_by_limitation_offset;
}

char* generate_an_array_by_limitation(int limitation, void* insert)
{

    char* array = malloc(limitation*sizeof(char));

    for (int iteration = 0; iteration < limitation; iteration++)
    {
        array[iteration] = (char)insert;
    }

    return array;
}

void assign_header_by_limitation(int cacheLimitation, int endOfHeader, char* protocol_header, char* block_to_fill, void* insert)
{

    for (int iteration = 0; iteration < cacheLimitation; iteration++)
    {
        if (iteration < endOfHeader)
        {
            block_to_fill[iteration] = protocol_header[iteration];
        }

        else {
            block_to_fill[iteration] = (char)insert;
        }
    }
}

// <cacheLimitation> The upper limit for the server per file | <endOfHeader> The upper limit of the header to write | <protocolHeader> The header content | <blockToFill> The pointer/array for the response | <contentPayload> The payload 
// ?What does it do¿: This function operates on a pointer to a block of cached memory that is being used as a response.
void assign_response_by_limitation_offset(int cacheLimitation, int endOfHeader, char* protocolHeader, char* blockToFill, char* contentPayload)
{

    for (int iteration = 0; iteration < cacheLimitation; iteration++)
    {
        if (iteration < endOfHeader)
        {
            blockToFill[iteration] = protocolHeader[iteration];
        }

        else {
            blockToFill[iteration] = contentPayload[iteration-endOfHeader];
        }
    }
}