#include "line.hpp"
#include <iostream>
#include "tgaimage.h"


void Line::testBresenhamLine(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
	// �趨һ����ת����ֵ����ͨ���Ƚ�dx��dy�Ĵ�С�����ж��Ƿ���Ҫ�������ꡣ
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	// �ж���㼰�յ�Ĵ�С��ȷ��������յ����ߣ������һ��ơ�
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	// ����dx��dy
	int dx = x1 - x0;
	int dy = y1 - y0;

	// Ԥ������p<0��p>0ʱ����������
	int derr2 = 2 * std::abs(dy);
	int derrxy2 = derr2 - 2 * dx;

	// �����һ���е�p��ֵ
	int p = derr2 - dx;

	// �����y�Ĳ���
	int y = y0;
	int y_step = y0 < y1 ? 1 : -1;

	// ��ʼѭ��������
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

		// ������һ���p��ֵ
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