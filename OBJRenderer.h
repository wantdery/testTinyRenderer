#pragma once
#include "Matrix4x4.h"
#include "tgaimage.h"

class OBJRenderer
{
public:
	OBJRenderer();
	~OBJRenderer();

	static void drawObj(const char* filepath, TGAImage& image, TGAColor color);

	static void drawTriangleObj(const char* filepath, TGAImage& image,Matrix4x4 mvpMatrix,int screen_width,int screen_height, TGAImage& imageDepth, TGAColor color);
};

