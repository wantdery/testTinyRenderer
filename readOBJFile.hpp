
#pragma once
#include "tgaimage.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Matrix4x4.h"
#include "Vector3f.h"

struct Vertex
{
	float x, y, z;
};

struct FaceVertex
{
	int vertexIndex;
	int texCoordIndex;
	int normalIndex;
};

struct Face
{
	std::vector<FaceVertex> vertices;
};

struct OBJInfo
{
	std::vector<Vector3f> vertices;
	std::vector<Face> faces;
};


class OBJReader {
public:
	OBJReader()
	{
	}

	~OBJReader() {}

	static OBJInfo readOBJFile(const char* filename);

	static void process_line(const std::string& line, std::vector<Vector3f>& vertices,
		std::vector<Face>& faces);

	static Vector3f transformNDCVertex(Vector3f& vertex, float screen_width, float screen_height) {
		float transNDCCoordX = (vertex.x + 1) / 2.f;
		float transNDCCoordY = (vertex.y + 1) / 2.f;

		float finalCoordX = transNDCCoordX * screen_width;
		float finalCoordY = transNDCCoordY * screen_height;

		return Vector3f{ finalCoordX, finalCoordY, vertex.z };
	}



	static Vector3f transformNDCVertexNew(Vector4f& vertex, float screen_width, float screen_height) {

		float f1 = (100 - 0.1) / 2.0;
		float f2 = (100 + 0.1) / 2.0;

		//get_view_matrix(screen_width, screen_height);
		float transNDCCoordX = (vertex.x + 1) / 2.f * screen_width;
		float transNDCCoordY = (vertex.y + 1) / 2.f * screen_height;

		//float finalCoordX = transNDCCoordX * screen_width;
		//float finalCoordY = transNDCCoordY * screen_height;

		return Vector3f{ transNDCCoordX, transNDCCoordY, vertex.z * f1 + f2 };
	}

private:
	static Matrix4x4 get_view_matrix(float width, float height)
	{
		double view[4][4] = {
			{width / 2  ,0          ,0          ,width / 2 },
			{0          ,height / 2 ,0          ,height / 2},
			{0          ,0          ,1          ,0         },
			{0          ,0          ,0          ,1         }
		};
		Matrix4x4 viewMatrix = Matrix4x4(view);
		return viewMatrix;
	}
};

