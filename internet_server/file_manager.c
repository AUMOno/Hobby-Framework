#ifndef IO_LIBRAIRES_H 
#include "headers/io_libraries.h"
#define IO_LIBRAIRES_H
#endif

#ifndef CACHE_MANAGER_H 
#include "headers/cache_manager.h"
#define CACHE_MANAGER_H
#endif

#ifndef FILE_MANAGER_H
#include "headers/file_manager.h"
#define FILE_MANAGER_H
#endif

struct FileManager {
    void(*reassemble_this)();
    FILE*(*read_file_path)(const char*, char);
    void(*print_file)();
    void(*display_cached_block)();
    char*(*collect_file)();
    char*(*collect_file_from_offset)();
};

void assemble_file_manager(struct FileManager* delegate) {
    delegate->reassemble_this = assemble_file_manager;
    delegate->read_file_path = read_file_path;
    delegate->print_file = print_file;
    delegate->display_cached_block = display_cached_block;
    delegate->collect_file = collect_file;
    delegate->collect_file_from_offset = collect_file_from_offset;
}

FILE* read_file_path(const char* path, char print)
{

    FILE* file = fopen(path, "r");

    if (file == NULL)
    {
        perror("File not found!");
    }

    else if (print == 'p')
    {
        print_file(file);
        printf("\n\n\n\n");
    }

    return file;
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

    rewind(file);
}

void display_cached_block(char* cachedBlock)
{

    for (int iteration = 0; iteration < CACHE_LIMITATION; iteration++)
    {
        putchar(cachedBlock[iteration]);
    }
    putchar('\n');
}

char* collect_file(FILE* fileToCollect, void* insert, char* base_file)
{
    rewind(fileToCollect);
    int _char;

    if (fileToCollect == NULL)
    {
        printf("The file could not be read. Please try checking the path, "
        "as you may be working in an environment that requires the full path " 
        "instead of the relative path.\n");
    }

    int i = 0;
    while ((_char = fgetc(fileToCollect)) != EOF)
    {
        base_file[i++] = _char;
    }

    rewind(fileToCollect);
    return base_file;
}

// <FILE> file to read | <baseFile> RAM allocation to fill | <startPoint> offset to fill from
// ?What does it do¿: This function appends data from a file without overwriting headers from a specified location.
char* collect_file_from_offset(FILE* fileToCollect, char* baseFile, int startPoint)
{
    rewind(fileToCollect);
    int _char;

    if (fileToCollect == NULL)
    {
        printf("The file could not be read. Please try checking the path, "
        "as you may be working in an environment that requires the full path " 
        "instead of the relative path.\n");
    }

    int i = 0;
    while ((_char = fgetc(fileToCollect)) != EOF)
    {
        baseFile[startPoint+i++] = _char;
    }

    rewind(fileToCollect);
    return baseFile;
}