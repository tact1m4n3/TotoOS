#pragma once

#include <core/utils.h>

struct FrameBuffer
{
	void* BaseAddress;
	uint64_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
};

struct Psf1Header
{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charSize;
};

struct Psf1Font
{
	Psf1Header* psf1Header;
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
    FrameBuffer* currentFrameBuffer;
    Psf1Font* activeFont;
private:
    uint32_t* videoBuffer;
public:
    Renderer(FrameBuffer* _frameBuffer, Psf1Font* _activeFont, RGBColor _bgColor);
    ~Renderer();

    void DrawPixel(int _posX, int _posY, RGBColor _color);
    void DrawRectangle(int _posX, int _posY, int _sizeX, int _sizeY, int _borderSize, RGBColor _fgColor, RGBColor _bgColor);
    void DrawChar(int _posX, int _posY, unsigned char c, int _fontSize, RGBColor _fontColor, RGBColor _bgColor);
    void Clear(RGBColor _bgColor);
private:
    uint32_t RGBToLegacyColor(RGBColor _color);
};
