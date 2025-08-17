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
		//通过向量叉积，计算三角形面积没问题，问题在于norm()会带入z，这个值是不用的，导致这里的结果计算有问题
		//Vector3f ac = ta - tc;
  //      Vector3f bc = tb - tc;
  //      return ac.cross(bc).norm() / 2;

		// 更新计算方式
		float x1 = ta.x - tc.x;
        float x2 = tb.x - tc.x;
        float y1 = ta.y - tc.y;
        float y2 = tb.y - tc.y;

		// 计算2d向量叉积，直接将z轴设为0
		return .5 * (x1 * y2 - x2 * y1);

	}

	// 鞋带公式（测量员公式、高斯面积公式，用于计算多边形面积），这里用于计算三角形面积，且由于需要用于背面剔除，所以需要保留符号
	static double signed_triangle_area(int ax, int ay, int bx, int by, int cx, int cy) {
		return .5 * ((by - ay) * (bx + ax) + (cy - by) * (cx + bx) + (ay - cy) * (ax + cx));
	}


	Vector4f vectices[3];
	std::vector<Vector4f> v;
private:
};



