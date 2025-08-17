#pragma once
#include <vector>
#include "Vector3f.h"
#include "line.hpp"
#include "Vector4f.h"

class Triangle
{
public:

	Triangle(Vector4f a, Vector4f b, Vector4f c)
		: vectices{ a, b, c }
	{

	};

	Triangle()
		: vectices{ Vector4f(), Vector4f(), Vector4f() }
	{

	};


	static void drawTriangleWire(Triangle& t, TGAImage& image, TGAColor color);

	static void oldSchoolDraw(Triangle& t, TGAImage& image, TGAColor Acolor, TGAColor Bcolor);

	static void drawTriangle(Triangle& t, TGAImage& image, TGAImage& imageDepth, TGAColor color);

	static std::tuple<float, float, float> centroidCoordinate(Vector4f& ta, Vector4f& tb, Vector4f& tc, Vector3f& centroid)
	{
		float alpha = ((centroid.y - tb.y) * (tc.x - tb.x) - (centroid.x - tb.x) * (tc.y - tb.y)) / ((ta.y - tb.y) * (tc.x - tb.x) - (ta.x - tb.x) * (tc.y - tb.y));
		float beta = ((centroid.y - tc.y) * (ta.x - tc.x) - (centroid.x - tc.x) * (ta.y - tc.y)) / ((tb.y - tc.y) * (ta.x - tc.x) - (tb.x - tc.x) * (ta.y - tc.y));
		float gamma = (1 - alpha - beta);

		return std::make_tuple(alpha, beta, gamma);
	};

	static float signed_triangle_area(Vector4f& ta, Vector4f& tb, Vector4f& tc)
	{
		//ͨ������������������������û���⣬��������norm()�����z�����ֵ�ǲ��õģ���������Ľ������������
		//Vector3f ac = ta - tc;
  //      Vector3f bc = tb - tc;
  //      return ac.cross(bc).norm() / 2;

		// ���¼��㷽ʽ
		float x1 = ta.x - tc.x;
        float x2 = tb.x - tc.x;
        float y1 = ta.y - tc.y;
        float y2 = tb.y - tc.y;

		// ����2d���������ֱ�ӽ�z����Ϊ0
		return .5 * (x1 * y2 - x2 * y1);

	}

	// Ь����ʽ������Ա��ʽ����˹�����ʽ�����ڼ���������������������ڼ����������������������Ҫ���ڱ����޳���������Ҫ��������
	static double signed_triangle_area(int ax, int ay, int bx, int by, int cx, int cy) {
		return .5 * ((by - ay) * (bx + ax) + (cy - by) * (cx + bx) + (ay - cy) * (ax + cx));
	}


	Vector4f vectices[3];
	std::vector<Vector4f> v;
private:
};



