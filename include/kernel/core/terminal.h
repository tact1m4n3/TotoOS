#pragma once

#include <core/utils.h>

class Terminal
{
public:
    Terminal(FrameBuffer* _frameBuffer, int _startX, int _startY, int _sizeX, int _sizeY, uint32_t _bgColor, uint32_t _fgColor);
    ~Terminal();
private:

};

