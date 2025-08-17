#pragma once
#include "tgaimage.h"

class Line
{
public:
	static void testBresenhamLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);

	static void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
};