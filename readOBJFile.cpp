#include "readOBJFile.hpp"

#include "line.hpp"

void OBJReader::process_line(const std::string& line, std::vector<Vector3f>& vertices,
	std::vector<Face>& faces)
{
	std::stringstream ss(line);
	std::string prefix;

	ss >> prefix;

	Vector3f vetex;
	Face face;

	if (prefix == "v")
	{
		float x, y, z;
		ss >> x >> y >> z;
		vetex.x = x;
		vetex.y = y;
		vetex.z = z;

		vertices.push_back(vetex);
	}
	else if (prefix == "f")
	{
		std::string vertex_block;

		while (ss >> vertex_block)
		{
			std::stringstream line_ss(vertex_block);
			FaceVertex fv;
			char slash;

			line_ss >> fv.vertexIndex >> slash >> fv.texCoordIndex >> slash >> fv.normalIndex;

			if (line_ss.fail())
			{
				// 如果解析失败，可能是其他格式，这里为了简单先忽略
				std::cerr << "警告: 无法完全解析数据块" << vertex_block << "可能格式不匹配。" << std::endl;
				continue;
			}

			fv.vertexIndex -= 1;
			fv.texCoordIndex -= 1;
			fv.normalIndex -= 1;

			// 将解析出的顶点索引信息添加到面中
			face.vertices.push_back(fv);
		}

		if (face.vertices.size() == 3)
		{
			faces.push_back(face);
		}
	}
}


OBJInfo OBJReader::readOBJFile(const char* filename )
{
	std::string line;
	std::vector <std::string> lines;

	std::ifstream readFile(filename);

	std::vector<Vector3f> vertexList;
	std::vector<Face> faceList;

	OBJInfo objInfo = OBJInfo();

	if (!readFile.is_open())
	{
		std::cerr << "could not read this OBJ file!" << '\n';

		return objInfo;
	}

	

	int index = 0;

	while (std::getline(readFile, line))
	{
		//lines.push_back(filename);

		process_line(line, objInfo.vertices, objInfo.faces);

		//std::cout << line << '\n';
	}

	return objInfo;
}

