typedef unsigned long long size_t;

typedef struct
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
} FrameBuffer;

typedef struct 
{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charSize;
} PSF1_HEADER;

typedef struct 
{
	PSF1_HEADER* psf1Header;
	void* glyphBuffer;
} PSF1_FONT;

void PutChar(FrameBuffer* frameBuffer, PSF1_FONT* psf1Font, unsigned int color, char c, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)frameBuffer->BaseAddress;
    char* fontPtr = psf1Font->glyphBuffer + (c * psf1Font->psf1Header->charSize);

    for (unsigned long y = yOff; y < yOff + 16; ++y)
    {
        for (unsigned long x = xOff; x < xOff + 8; ++x)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int*)(pixPtr + x + (y * frameBuffer->PixelsPerScanLine)) = color;
            }
        }

        ++fontPtr;
    }
}

void main(FrameBuffer* frameBuffer, PSF1_FONT* psf1Font)
{
    PutChar(frameBuffer, psf1Font, 0xffffffff, 'G', 20, 20);

    return;
}