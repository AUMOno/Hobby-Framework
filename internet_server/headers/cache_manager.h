#ifndef CACHE_MANAGER_H
#define CACHE_MANAGER_H

typedef void* any;

#define BASE_FILE_LIMITATION 1024
#define STATIC_FILE_COUNT_LIMIT 16
#define CACHE_LIMITATION (BASE_FILE_LIMITATION * STATIC_FILE_COUNT_LIMIT)
#define PAYLOAD_LIMITATION (CACHE_LIMITATION - BASE_FILE_LIMITATION)

char* generate_an_array_by_limitation(int limitation, void* insert);
void assign_header_by_limitation(int cacheLimitation, int endOfHeader, char* protocol_header, char* block_to_fill, void* insert);
void assign_response_by_limitation_offset(int cacheLimitation, int endOfHeader, char* protocolHeader, char* blockToFill, char* contentPayload);

#endif