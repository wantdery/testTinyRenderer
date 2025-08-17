#define _USE_MATH_DEFINES

// ANSI 转义序列颜色代码
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#include "OBJRenderer.h"
#include <algorithm>
#include <cmath>
#include "line.hpp"
#include <iostream>
#include <vector>
#include "readOBJFile.hpp"
#include "Triangle.h"
#include <array>
#include <limits>

#include "Matrix4x4.h"

void OBJRenderer::drawObj(const char* filepath, TGAImage& image, TGAColor color)
{
	float screen_width = 500;
	float screen_height = 500;

	std::vector<Vector3f> vertexList;


	//readOBJFile("../obj/diablo3_pose/diablo3_pose.obj", objInfo);
	OBJInfo objInfo = OBJReader::readOBJFile(filepath);

	std::cout << objInfo.faces.size() << "  " << objInfo.vertices.size() << '\n';

	for (auto v : objInfo.vertices)
	{
		vertexList.push_back(OBJReader::transformNDCVertex(v, screen_width, screen_height));
	}


	std::vector<std::array<Vector3f, 3>> triangles;

	for (auto f : objInfo.faces)
	{
		int index_0 = f.vertices[0].vertexIndex;
		int index_1 = f.vertices[1].vertexIndex;
		int index_2 = f.vertices[2].vertexIndex;

		Vector3f p0 = vertexList[index_0];
		Vector3f p1 = vertexList[index_1];
		Vector3f p2 = vertexList[index_2];

		std::array<Vector3f, 3> arr = { p0, p1, p2 };

		triangles.push_back(arr);

		//Line::testBresenhamLine(std::round(p0.x), std::round(p0.y), std::round(p1.x), std::round(p1.y), image, color);
		//Line::testBresenhamLine(std::round(p1.x), std::round(p1.y), std::round(p2.x), std::round(p2.y), image, color);
		//Line::testBresenhamLine(std::round(p2.x), std::round(p2.y), std::round(p0.x), std::round(p0.y), image, color);
	}

	std::sort(triangles.begin(), triangles.end(), [&](const std::array<Vector3f, 3>& a, const std::array<Vector3f, 3>& b)
		{
			float aminz = std::min(a[0].z,
				std::min(a[1].z,
					a[2].z));
			float bminz = std::min(b[0].z,
				std::min(b[1].z,
					b[2].z));
			return aminz < bminz;
		});



	for (auto& t : triangles)
	{
		Line::testBresenhamLine(std::round(t[0].x), std::round(t[0].y), std::round(t[1].x), std::round(t[1].y), image, color);
		Line::testBresenhamLine(std::round(t[1].x), std::round(t[1].y), std::round(t[2].x), std::round(t[2].y), image, color);
		Line::testBresenhamLine(std::round(t[2].x), std::round(t[2].y), std::round(t[0].x), std::round(t[0].y), image, color);

	}
}


void OBJRenderer::drawTriangleObj(const char* filepath, TGAImage& image, Matrix4x4 mvpMatrix, int screen_width, int screen_height, TGAImage& imageDepth, TGAColor color)
{
	std::vector<Vector3f> vertexList;
	std::vector<Triangle> triangleList;


	//readOBJFile("../obj/diablo3_pose/diablo3_pose.obj", objInfo);
	OBJInfo objInfo = OBJReader::readOBJFile(filepath);

	std::cout << objInfo.faces.size() << "  " << objInfo.vertices.size() << '\n';

	std::vector<Vector4f> screen_coords; // 存储变换到屏幕空间的坐标

	//mvpMatrix.print();

	// 顶点变换阶段，此时我们存储的是模型空间下的顶点坐标，需要先通过mvp矩阵将坐标变换到裁剪空间
	for (auto v : objInfo.vertices)
	{
		std::cout << "一个端点" << '\n';
		//std::cout << GREEN << v.x << " " << v.y << " " << v.z << RESET << '\n';

		// 从模型坐标构建齐次坐标向量
		Vector4f v_clip = Vector4f(v.x, v.y, v.z, 1.f);

		// 应用MVP变换，得到裁剪空间坐标
		v_clip = mvpMatrix * v_clip;

		// 接下来，进行透视除法，获取NDC坐标
		Vector4f v_ndc;
		if (std::abs(v_clip.w) > 1e-6)
		{
			v_ndc.x = v_clip.x / v_clip.w;
			v_ndc.y = v_clip.y / v_clip.w;
			v_ndc.z = v_clip.z / v_clip.w;
		}
		else
		{
			v_ndc = Vector4f(0, 0, 0, 0);
		}

		// 视口变换，将NDC坐标映射到屏幕坐标
		Vector4f v_screen;
		v_screen.x = (v_ndc.x + 1.f) * screen_width / 2.f;
		v_screen.y = (1.f - v_ndc.y) * screen_height / 2.f;

		v_screen.z = (v_ndc.z + 1.f) / 2.f;
		v_screen.w = v_clip.w;

		screen_coords.push_back(v_screen);

		//std::cout << YELLOW << v_clip.x << " " << v_clip.y << " " << v_clip.z << " " << v_clip.w << RESET << '\n';
		//std::cout << CYAN << v_ndc.x << " " << v_ndc.y << " " << v_ndc.z << RESET << '\n';
		std::cout << GREEN << v_screen.x << " " << v_screen.y << " " << v_screen.z << RESET << '\n';

		//vertexList.push_back(OBJReader::transformNDCVertexNew(newV, screen_width, screen_height));
	}

	for (auto f : objInfo.faces)
	{
		int index_0 = f.vertices[0].vertexIndex;
		int index_1 = f.vertices[1].vertexIndex;
		int index_2 = f.vertices[2].vertexIndex;

		Vector4f p0 = screen_coords[index_0];
		Vector4f p1 = screen_coords[index_1];
		Vector4f p2 = screen_coords[index_2];

		Triangle t(p0, p1, p2);

		Triangle::drawTriangle(t, image, imageDepth, TGAColor(255 * std::rand(), 255 * std::rand(), 255 * std::rand(), 255));
	}

	// 画家算法，对于z值进行排序，性能低下
	//std::sort(triangleList.begin(), triangleList.end(), [](const Triangle& t1, const Triangle& t2)
	//	{
	//		float aminz = std::min(t1.vectices[0].z,
	//			std::min(t1.vectices[1].z,
	//				t1.vectices[2].z));
	//		float bminz = std::min(t2.vectices[0].z,
	//			std::min(t2.vectices[1].z,
	//				t2.vectices[2].z));

	//		return aminz < bminz;
	//	});

	//

 //   for (auto& t : triangleList)
 //   {
	//	for (auto& v : t.vectices)
	//	{
	//	std::cout << 'z' << v.z << '\n';
	//	}
	//	std::cout << '\n';

 //       Triangle::drawTriangle(t, image, TGAColor(255 * std::rand(), 255 * std::rand(), 255 * std::rand(), 255));
 //   }

}

