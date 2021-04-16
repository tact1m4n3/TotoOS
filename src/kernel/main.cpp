#include <core/utils.h>
#include <core/renderer.h>
#include <core/terminal.h>

extern "C" void main(FrameBuffer* frameBuffer, Psf1Font* psf1Font)
{
    Renderer renderer(frameBuffer, psf1Font, {132, 156, 247});

	Terminal terminal(400, 100, 1920 - 400 * 2, 1080 - 100 * 2, 2, {0, 0, 0}, {255, 255, 255});

	terminal.Print((char*)"Hellooooooooooooooooooooooooooooooooooooooooo\n");
	terminal.Print((char*)"Hellooooooooooooooooooooooooooooooooooooooooo");

	while(1);
}