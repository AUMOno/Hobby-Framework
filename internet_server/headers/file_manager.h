#ifndef FILE_MANAGER_H

#ifndef IO_LIBRAIRES_H 
#include "io_libraries.h"
#define IO_LIBRAIRES_H
#endif

FILE* read_file_path(const char* path, char print);
void print_file(FILE* file);
void display_cached_block(char* cachedBlock);
char* collect_file(FILE* fileToCollect, void* insert, char* base_file);
char* collect_file_from_offset(FILE* fileToCollect, char* baseFile, int startPoint);

#define CACHE_MANAGER_H
#endif