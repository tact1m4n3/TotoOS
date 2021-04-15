#pragma once

#include <core/utils.h>

struct FrameBuffer
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
};

struct PSF1_HEADER
{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charSize;
};

struct Psf1Font
{
	PSF1_HEADER* psf1Header;
	void* glyphBuffer;
};

struct RGBColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Renderer
{
public:
    static Renderer* activeRenderer;
private:
    FrameBuffer* currentFrameBuffer;
    Psf1Font* activeFont;
    uint32_t* videoBuffer;
public:
    Renderer(FrameBuffer* _frameBuffer, Psf1Font* _activeFont, RGBColor _bgColor);
    ~Renderer();

    void DrawPixel(int _posX, int _posY, RGBColor _color);
    void DrawRectangle(int _posX, int _posY, int _sizeX, int _sizeY, RGBColor _color);
    void DrawChar(int _posX, int _posY, unsigned char c, RGBColor _fontColor, RGBColor _bgColor);
    void Clear(RGBColor _bgColor);
private:
    uint32_t RGBToLegacyColor(RGBColor _color);
};
