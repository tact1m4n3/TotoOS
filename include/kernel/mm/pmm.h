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

class PhysicalMemoryManager
{
private:
    static PhysicalMemoryManager* instance;

    EfiMemoryDescriptor* memoryMap;
    uint64_t memoryMapSize;
    uint64_t memoryMapDescriptorSize;

    uint64_t freedPages[1024];
    uint64_t fpsp;

    uint64_t lastPage;
public:
    PhysicalMemoryManager(EfiMemoryDescriptor* _memoryMap, uint64_t _memoryMapSize, uint64_t _memoryMapDescriptorSize);
    ~PhysicalMemoryManager() {}

    uint64_t AllocatePage();
    void FreePage(uint64_t page);

    void PrepareMore();
};
