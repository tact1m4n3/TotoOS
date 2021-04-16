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
    void PutChar(char _c);
    void Clear(RGBColor _bgColor);
private:

};

