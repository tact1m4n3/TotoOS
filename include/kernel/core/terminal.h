#pragma once

#include <core/utils.h>
#include <core/renderer.h>

class Terminal
{
public:
    static Terminal* activeTerminal;
private:
    int startX, startY;
    int sizeX, sizeY;
    int cursorX, cursorY;

    int fontSize;
    int charsPerLine;

    RGBColor fontColor;
    RGBColor bgColor;
public:
    Terminal(int _startX, int _startY, int _sizeX, int _sizeY, int _fontSize, RGBColor _fontColor, RGBColor _bgColor);
    ~Terminal();

    void Print(char* _str);
    void PrintNumber(uint64_t num);
    void PrintHex(uint64_t num);
    void PutChar(char _c);
    void Clear(RGBColor _bgColor);
public:
    inline const RGBColor GetFontColor() { return fontColor; };
    inline const void SetFontColor(RGBColor _color) { fontColor = _color; };

    inline const RGBColor GetBackgroundColor() { return bgColor; };
    inline const void SetBGColor(RGBColor _color) { bgColor = _color; };

    inline const void SetFontSize(int _fontSize) { fontSize = _fontSize; };
};

