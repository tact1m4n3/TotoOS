#include <mm/pmm.h>

#include <core/terminal.h>

char* EfiMemoryTypeNames[] {

    "EfiReservedMemoryType",
    "EfiLoaderCode",
    "EfiLoaderData",
    "EfiBootServicesCode",
    "EfiBootServicesData",
    "EfiRuntimeServicesCode",
    "EfiRuntimeServicesData",
    "EfiConventionalMemory",
    "EfiUnusableMemory",
    "EfiACPIReclaimMemory",
    "EfiACPIMemoryNVS",
    "EfiMemoryMappedIO",
    "EfiMemoryMappedIOPortSpace",
    "EfiPalCode",
};

PhysicalMemoryManager* PhysicalMemoryManager::instance = nullptr;

PhysicalMemoryManager::PhysicalMemoryManager(EfiMemoryDescriptor* _memoryMap, uint64_t _memoryMapSize, uint64_t _memoryMapDescriptorSize)
{
    instance = this;

    memoryMap = _memoryMap;
    memoryMapSize = _memoryMapSize;
    memoryMapDescriptorSize = _memoryMapDescriptorSize;

    fpsp = 1024;

    lastPage = 0;

    PrepareMore();
}

uint64_t PhysicalMemoryManager::AllocatePage()
{
    if (fpsp >= 1024)
        PrepareMore();

    return freedPages[fpsp++];
}

void PhysicalMemoryManager::FreePage(uint64_t page)
{
    freedPages[--fpsp] = page;
}

void PhysicalMemoryManager::PrepareMore()
{
    uint64_t memoryMapEntries = memoryMapSize / memoryMapDescriptorSize;
	for (int i = 0; i < memoryMapEntries; ++i)
	{
		EfiMemoryDescriptor* desc = (EfiMemoryDescriptor*)((uint64_t)memoryMap + i * memoryMapDescriptorSize);

        if (lastPage > (uint64_t)desc->physAddr)
            continue;

		if (desc->type == MEM_TYPE_CONVENTIONAL_MEMORY)
		{
            for (int j = 0; j < desc->numPages; ++j)
            {
                if (lastPage > (uint64_t)desc->physAddr + j * 0x1000)
                    continue;
                if (fpsp <= 0)
                    break;
                lastPage = (uint64_t)desc->physAddr + j * 0x1000;
                FreePage(lastPage);
            }

            if (fpsp <= 0)
                break;
		}
	}
}

