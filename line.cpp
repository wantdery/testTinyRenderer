#include "line.hpp"
#include <iostream>
#include "tgaimage.h"


void Line::testBresenhamLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	// 设定一个反转布尔值，并通过比较dx和dy的大小，来判断是否需要交换坐标。
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	// 判断起点及终点的大小，确保起点在终点的左边，从左到右绘制。
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	// 计算dx和dy
	int dx = x1 - x0;
	int dy = y1 - y0;

	// 预计算在p<0和p>0时，误差的增量
	int derr2 = 2 * std::abs(dy);
	int derrxy2 = derr2 - 2 * dx;

	// 计算第一个中点p的值
	int p = derr2 - dx;

	// 计算好y的步长
	int y = y0;
	int y_step = y0 < y1 ? 1 : -1;

	// 开始循环绘制线
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}

		// 计算下一点的p的值
		if (p < 0)
		{
			p += derr2;
		}
		else
		{
			y += y_step;
			p += derrxy2;
		}
	}
}

void Line::line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	//for (float t = 0; t < 1.f; t += 0.01f)
	//{

	//	int x = x0 + (x1 - x0) * t;
	//	int y = y0 + (y1 - y0) * t;
	//	image.set(x, y, color);
	//}
	bool steep = false;

	if (std::abs(x1 - x0) < std::abs(y1 - y0))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	for (int x = x0; x <= x1; x++)
	{
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1. - t) + y1 * t;
		if (steep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}

	}
}