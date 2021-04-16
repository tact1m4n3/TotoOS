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

void Renderer::DrawRectangle(int _posX, int _posY, int _sizeX, int _sizeY, int _borderSize, RGBColor _fgColor, RGBColor _bgColor)
{
    for (int i = 0; i < _sizeY; ++i)
    {
        for (int j = 0; j < _sizeX; ++j)
        {
            if ((i < _borderSize) || (j < _borderSize) || (j >= _sizeX - _borderSize) || (i >= _sizeY - _borderSize))
                DrawPixel(_posX + j, _posY + i, _fgColor);
            else
                DrawPixel(_posX + j, _posY + i, _bgColor);
        }
    }
}

void Renderer::DrawChar(int _posX, int _posY, unsigned char _c, int _fontSize, RGBColor _fontColor, RGBColor _bgColor)
{
    uint8_t* fontBitmap = (uint8_t*)((size_t)activeFont->glyphBuffer + 16 * _c);

    for (int j = 1; j <= 16; ++j)
        for (int i = 1; i <= 8; ++i)
            if (fontBitmap[j] & (1 << 8-i))
                for (int k = 0; k < _fontSize; ++k)
                    for (int l = 0; l < _fontSize; ++l)
                        videoBuffer[_posX + l + i * _fontSize + (_posY + k-1 + j * _fontSize) * currentFrameBuffer->PixelsPerScanLine] = RGBToLegacyColor(_fontColor);
}

void Renderer::Clear(RGBColor _bgColor)
{
    for (int i = 0; i < currentFrameBuffer->Height; ++i)
        for (int j = 0; j < currentFrameBuffer->Width; ++j)
            DrawPixel(j, i, _bgColor);
}

uint32_t Renderer::RGBToLegacyColor(RGBColor _color)
{
    return (_color.r << 16) | (_color.g << 8) | _color.b;
}
