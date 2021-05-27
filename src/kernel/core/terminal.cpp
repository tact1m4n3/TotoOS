#include <core/terminal.h>

Terminal* Terminal::activeTerminal = nullptr;

Terminal::Terminal(int _startX, int _startY, int _sizeX, int _sizeY, int _fontSize, RGBColor _fontColor, RGBColor _bgColor)
{
    startX = _startX;
    startY = _startY;
    sizeX = _sizeX;
    sizeY = _sizeY;

    cursorX = 0;
    cursorY = 0;

    fontSize = _fontSize;

    charsPerLine = sizeX / (8 * fontSize);

    fontColor = _fontColor;
    bgColor = _bgColor;

    Clear(bgColor);

    activeTerminal = this;
}

Terminal::~Terminal()
{
}

void Terminal::Print(char* _str)
{
    for (char* ptr = _str; *ptr != '\0'; ++ptr)
        PutChar(*ptr);
}

void Terminal::PrintNumber(uint64_t num)
{
    Print(convert(num, 10));
}

void Terminal::PrintHex(uint64_t num)
{
    Print("0x");
    Print(convert(num, 16));
}

void Terminal::PutChar(char _c)
{
    if (_c == '\n')
    {
        cursorX = 0;
        ++cursorY;
    }
    else if (_c == '\t')
    {
        cursorX += 4;
    }
    else
    {
        Renderer::activeRenderer->DrawChar(startX + cursorX * 8 * fontSize, startY + cursorY * 16 * fontSize, _c, fontSize, fontColor, bgColor);
        ++cursorX;
    }

    if (cursorX >= charsPerLine)
    {
        cursorX = 0;
        ++cursorY;
    }
}

void Terminal::Clear(RGBColor _bgColor)
{
    bgColor = _bgColor;

    Renderer::activeRenderer->DrawRectangle(startX - 1, startY - 1, sizeX + 2, sizeY + 2, 1, {0, 0, 0}, bgColor);
}
