#include "Triangle.h"
#include <iostream>
#include <vector>


void Triangle::drawTriangleWire(Triangle& t, TGAImage& image, TGAColor color)
{
	Line::testBresenhamLine(
		t.vectices[0].x, t.vectices[0].y, t.vectices[1].x, t.vectices[1].y, image, color);
	Line::testBresenhamLine(
		t.vectices[1].x, t.vectices[1].y, t.vectices[2].x, t.vectices[2].y, image, color);
	Line::testBresenhamLine(
		t.vectices[2].x, t.vectices[2].y, t.vectices[0].x, t.vectices[0].y, image, color);
}

// 老派画三角形，先画三角形的中间点的下半部分，再从中间点继续向上绘制，实际遍历的像素之后这个三角形本身
void Triangle::oldSchoolDraw(Triangle& t, TGAImage& image, TGAColor Acolor, TGAColor Bcolor)
{
	float maxY = std::max(t.vectices[0].y, std::max(t.vectices[2].y, t.vectices[1].y));
	float maxY1 = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int round = 0; round < 2 - i; round++)
		{
			if (t.vectices[round].y > t.vectices[round + 1].y)
			{
				std::swap(t.vectices[round], t.vectices[round + 1]);
			}
		}
	}

	int totalHeight = t.vectices[2].y - t.vectices[0].y;

	int sx1 = 0;
	int sx2 = 0;
	if (t.vectices[0].y != t.vectices[1].y)
	{
		int segmentHeight = t.vectices[1].y - t.vectices[0].y;
		for (int y = t.vectices[0].y; y < t.vectices[1].y; y++)
		{
			int x1 = t.vectices[0].x + (t.vectices[2].x - t.vectices[0].x) * ((y - t.vectices[0].y) / totalHeight);
			int x2 = t.vectices[0].x + (t.vectices[1].x - t.vectices[0].x) * ((y - t.vectices[0].y) / segmentHeight);

			for (int x = std::min(x1, x2); x < std::max(x1, x2); x++)  // draw a horizontal line
				image.set(x, y, Acolor);
		}
	}

	if (t.vectices[2].y != t.vectices[1].y)
	{
		int segmentHeight1 = t.vectices[2].y - t.vectices[1].y;
		for (int y = t.vectices[1].y; y < t.vectices[2].y; y++)
		{
			int x1 = t.vectices[0].x + (t.vectices[2].x - t.vectices[0].x) * (y - t.vectices[0].y) / totalHeight;
			int x2 = t.vectices[1].x + (t.vectices[2].x - t.vectices[1].x) * (y - t.vectices[1].y) / segmentHeight1;

			std::cout << "x1:" << x1 << "  " << " x2:" << x2 << std::endl;

			for (int x = std::min(x1, x2); x < std::max(x1, x2); x++)  // draw a horizontal line
				image.set(x, y, Acolor);
		}
	}
}

void Triangle::drawTriangle(Triangle& t, TGAImage& image, TGAImage& imageDepth, TGAColor color)
{
	float MaxX = std::max(t.vectices[0].x, std::max(t.vectices[1].x, t.vectices[2].x));
	float MinX = std::min(t.vectices[0].x, std::min(t.vectices[1].x, t.vectices[2].x));
	float MaxY = std::max(t.vectices[0].y, std::max(t.vectices[1].y, t.vectices[2].y));
	float MinY = std::min(t.vectices[0].y, std::min(t.vectices[1].y, t.vectices[2].y));

	//float area = signed_triangle_area(t.vectices[0].x, t.vectices[0].y,
	//	t.vectices[1].x, t.vectices[1].y, t.vectices[2].x, t.vectices[2].y);
	//float area1 = signed_triangle_area(t.vectices[0],
	//	t.vectices[1], t.vectices[2]);

	//if (area1 < 1) return;
	for (int x = MinX; x <= MaxX; x++)
	{
		for (int y = MinY; y <= MaxY; y++)
		{
			Vector3f p = Vector3f(x, y, 0);

			auto [alpha, beta, gamma] = centroidCoordinate(t.vectices[0], t.vectices[1], t.vectices[2], p);

			if (alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				//float depth = alpha * ((t.vectices[0].z + 1) / 2.f) + beta * ((t.vectices[1].z + 1) / 2.f) + gamma * ((t.vectices[2].z + 1) / 2.f);
				//float depth = alpha * t.vectices[0].z + beta * t.vectices[1].z + gamma * t.vectices[2].z;


				float w_inverse_p0 = 1.0f / t.vectices[0].w;
				float w_inverse_p1 = 1.0f / t.vectices[1].w;
				float w_inverse_p2 = 1.0f / t.vectices[2].w;

				float w_interpolate = alpha * w_inverse_p0 + beta * w_inverse_p1 + gamma * w_inverse_p2;
				float z_interpolate = alpha * t.vectices[0].z * w_inverse_p0 +
					beta * t.vectices[1].z * w_inverse_p1 + gamma * t.vectices[2].z * w_inverse_p2;

				float depth = z_interpolate / w_interpolate;

				//std::cout << "depth:  " << depth << std::endl;

				depth = depth * 255;

				if (imageDepth.get(x, y).r < depth)
				{

					TGAColor c = TGAColor(depth, depth, depth, 255);

					image.set(x, y, color);
					//image.set_depth(x, y, depth);
					imageDepth.set(x, y, c);
					//imageDepth.set(x, y, TGAColor(depth, depth, depth, 255));
				}
			}

		}
	}
}