#pragma once

#include <core/utils.h>

#define MEM_TYPE_CONVENTIONAL_MEMORY 7

struct EfiMemoryDescriptor
{
    uint32_t type;
    void* physAddr;
    void* virtualAddr;
    uint64_t numPages;
    uint64_t attribs;
};

extern char* EfiMemoryTypeNames[];
