#include <core/utils.h>
#include <core/renderer.h>
#include <core/terminal.h>
#include <mm/pmm.h>

struct BootInfo
{
	FrameBuffer* frameBuffer;
	Psf1Font* psf1Font;
	EfiMemoryDescriptor* memoryMap;
	uint64_t memoryMapSize;
	uint64_t memoryMapDescriptorSize;
};

extern "C" void main(BootInfo* bootInfo)
{
    Renderer renderer(bootInfo->frameBuffer, bootInfo->psf1Font, {132, 156, 247});

	Terminal terminal(400, 100, bootInfo->frameBuffer->Width - 400 * 2, bootInfo->frameBuffer->Height - 100 * 2, 2, {0, 0, 0}, {255, 255, 255});

	terminal.Print((char*)"Welcome to TotoOS...\n");

	// ---------------------------- System Specs ----------------------------------
	terminal.Print("Resolution: ");
	terminal.PrintNumber(bootInfo->frameBuffer->Width);
	terminal.Print("x");
	terminal.PrintNumber(bootInfo->frameBuffer->Height);
	terminal.Print("\nVideo Memory Buffer: ");
	terminal.PrintHex((uint64_t)bootInfo->frameBuffer->BaseAddress);
	terminal.Print("\n\n");
	// ----------------------------------------------------------------------------
	
	PhysicalMemoryManager pmm(bootInfo->memoryMap, bootInfo->memoryMapSize, bootInfo->memoryMapDescriptorSize);

	for (int i = 0; i < 3; ++i)
	{
		terminal.PrintHex(pmm.AllocatePage());
		terminal.Print("\n");
	}

	while(1);
}