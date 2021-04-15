#include <core/renderer.h>

Renderer* Renderer::activeRenderer;

Renderer::Renderer(FrameBuffer* _frameBuffer, Psf1Font* _activeFont, RGBColor _bgColor)
{
    currentFrameBuffer = _frameBuffer;
    activeFont = _activeFont;
    videoBuffer = (uint32_t*)_frameBuffer->BaseAddress;

    Clear(_bgColor);

    activeRenderer = this;
}

Renderer::~Renderer()
{
}

void Renderer::DrawPixel(int _posX, int _posY, RGBColor _color)
{
    videoBuffer[_posX + _posY * currentFrameBuffer->PixelsPerScanLine] = RGBToLegacyColor(_color);
}

void Renderer::DrawRectangle(int _posX, int _posY, int _sizeX, int _sizeY, RGBColor _color)
{

}

void Renderer::DrawChar(int _posX, int _posY, unsigned char c, RGBColor _fontColor, RGBColor _bgColor)
{
    uint8_t* fontBitmap = (uint8_t*)((size_t)activeFont->glyphBuffer + 16 * c);

    for (int j = 0; j < 16; ++j)
        for (int i = 0; i < 8; ++i)
            if (fontBitmap[j] & (1 << 8-i))
                videoBuffer[_posX + i + (_posY + j) * 1920] = RGBToLegacyColor(_fontColor);
            else
                videoBuffer[_posX + i + (_posY + j) * 1920] = RGBToLegacyColor(_bgColor);
}

void Renderer::Clear(RGBColor _bgColor)
{
    for (int i = 0; i < currentFrameBuffer->Height; ++i)
        for (int j = 0; j < currentFrameBuffer->Width; ++j)
            DrawPixel(j, i, _bgColor);
}

uint32_t Renderer::RGBToLegacyColor(RGBColor _color)
{
    return (_color.b << 16) | (_color.g << 8) | _color.r;
}
