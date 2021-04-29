#pragma once
#include <iostream>
#include <fstream>
using namespace std;

struct BmpSignature
{
	unsigned char data[2];
};

struct BmpHeader
{
	BmpSignature signature;
	uint32_t fileSize;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t dataOffset;
};

struct BmpDib
{
	uint32_t dibSize;
	int32_t imageWidth;
	int32_t imageHeight;
	uint16_t colorPlaneCount;
	uint16_t pixelSize;
	uint32_t compressMethod;
	uint32_t bitmapByteCount;
	int32_t horizontalResolution;
	int32_t verticalResolution;
	uint32_t colorCount;
	uint32_t importantColorCount;
};

struct Color
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct ColorTable
{
	Color* colors;
	uint32_t length;
};

struct PixelArray
{
	Color** pixels;
	uint32_t rowCount;
	uint32_t columnCount;
};

#include <Windows.h>

bool isBmpFile(FILE* f)
{
	if (f == NULL)
		return false;
	BmpSignature signature;
	fseek(f, 0, 0L);
	fread(&signature, sizeof(BmpSignature), 1, f);
	return signature.data[0] == 'B' && signature.data[1] == 'M';
}
void readBmpHeader(FILE* f, BmpHeader& header)
{
	if (f == NULL)
		return;
	fseek(f, 0, 0L);
	fread(&header, sizeof(BmpHeader), 1, f);
}

void printBmpHeader(BmpHeader header)
{
	printf("*** BMP Header ***\n");
	printf("- File Size   : &d byte(s)\n", header.fileSize);
	printf("- Reserved1   : &d\n", header.reserved1);
	printf("- Reserved2   : %d\n", header.reserved2);
	printf("- Data Offset: &d byte(s)\n", header.dataOffset);
}

void readBmbDib(FILE* f, BmpDib& dib)
{
	if (f == NULL)
		return;
	fseek(f, sizeof(BmpHeader), 0L);
	fread(&dib, sizeof(BmpDib), 1, f);
}

void printBmpDib(BmpDib dib)
{
	printf("- DIB Size				 : &d byte(s)\n", dib.dibSize);
	printf("- Image Width			 : &d\n", dib.imageWidth);
	printf("- Image Height			 : &d\n", dib.imageHeight);
	printf("- Number of Color Planes : &d\n", dib.colorPlaneCount);
	printf("- Pixel Size			 : &d bit(s)\n", dib.pixelSize);
	printf("- Compress Method		 : &d\n", dib.compressMethod);
	printf("- Bitmap Size			 : &d bytes(s)\n", dib.bitmapByteCount);
	printf("- Horizontal Resolution	 : &d\n", dib.horizontalResolution);
	printf("- Vertical Resolution	 : &d\n", dib.verticalResolution);
	printf("- Number of Colors		 : &d\n", dib.colorCount);
	printf("- Number of Impt Colors	 : &d\n", dib.importantColorCount);
}

void scanBmpPixelLine(FILE* f, Color*& line, uint32_t length)
{
	if (f == NULL)
		return;
	line = new Color[length];
	fread(line, sizeof(Color), length, f);
}

void skipBmpPadding(FILE* f, char count)
{
	if (f == NULL)
		return;
	if (count == 0)
		return;
	char padding[3];
	fread(padding, count, 1, f);
}

void readBmpPixelArray(FILE* f, BmpHeader header, BmpDib dib, PixelArray& data)
{
	if (f == NULL)
		return;
	data.rowCount = dib.imageHeight;
	data.columnCount = dib.imageWidth;
	data.pixels = new Color * [data.rowCount];

	char paddingCount = (4 - (dib.imageWidth * (dib.pixelSize / 8) % 4)) % 4;
	fseek(f, header.dataOffset, 0L);
	for (int i = 0; i < data.rowCount; i++)
	{
		scanBmpPixelLine(f, data.pixels[data.rowCount - 1 - i], dib.imageWidth);
		skipBmpPadding(f, paddingCount);
	}
}

void drawBmp(BmpDib dib, PixelArray data)
{
	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	for(int i = 0; i < dib.imageHeight; i++)
		for (int j = 0; j < dib.imageWidth; j++)
		{
			Color pixel = data.pixels[i][j];
			SetPixel(hdc, j, i, RGB(pixel.red, pixel.green, pixel.blue));
		}
	ReleaseDC(console, hdc);
}

void releaseBmpPixelArray(PixelArray data)
{
	for (int i = 0; i < data.rowCount; i++)
		delete[]data.pixels[i];
	delete[]data.pixels;
}
