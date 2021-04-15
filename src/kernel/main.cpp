#include <core/utils.h>
#include <core/renderer.h>

extern "C" void main(FrameBuffer* frameBuffer, Psf1Font* psf1Font)
{
    Renderer renderer(frameBuffer, psf1Font, (RGBColor){0, 0, 0});
	renderer.DrawPixel(100, 100, (RGBColor){244, 244, 244});
	renderer.DrawChar(10, 100, 'G', (RGBColor){244, 244, 244}, (RGBColor){0, 0, 0});

	while(1);
}