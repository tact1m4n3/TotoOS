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

void main(FrameBuffer* frameBuffer, PSF1_FONT* psf1Font)
{
    return;
}