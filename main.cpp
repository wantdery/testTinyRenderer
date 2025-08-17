#include <corecrt_math_defines.h>

#include "tgaimage.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "readOBJFile.hpp"
#include "line.hpp"
#include "Matrix4x4.h"
#include "OBJRenderer.h"
#include "Triangle.h"
#include "Vector3f.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

float toRadians(float degrees)
{
	return degrees * M_PI / 180.0;
}


Matrix4x4 get_project_matrix(float near, float far, float fov, float aspect_ratio)
{
	float fov_rad = toRadians(fov);

	float n = -near;
	float f = -far;
	float t = std::tan(fov_rad / 2.f) * std::abs(n);
	float b = -std::tan(fov_rad / 2.f) * std::abs(n);
	float l = -t * aspect_ratio;
	float r = t * aspect_ratio;


	double Bprojection[4][4] = {
	{n/r, 0, 0, 0},
	{0, n/t, 0, 0},
	{0, 0, -(f+n)/(f-n),-(2*f*n)/(f-n)},
	{0, 0, -1, 0}
	};

	Matrix4x4 newB = Matrix4x4(Bprojection);


	std::cout << "newB投影矩阵" << '\n';
	newB.print();
	std::cout << '\n';
	//std::cout << "老的投影矩阵" << '\n';
	//(orthogonalM * perspectiveMatrix).print();

	return newB;
	//return orthogonalMatrix * perspectiveMatrix;

}

Matrix4x4 get_view_matrix(Vector3f eye_position)
{
	double view[4][4] = {
		{1,0,0,-eye_position[0]},
		{0,1,0,-eye_position[1]},
		{0,0,1,-eye_position[2]},
		{0,0,0,1}
	};

	Matrix4x4 viewMatrix = Matrix4x4(view);

	return viewMatrix;
}


int main(int argc, char** argv) {
	float radians = 30 * M_PI / 180.0;

	Vector3f firstColumn = Vector3f(std::cos(radians), 0, std::sin(radians));
	Vector3f secondColumn = Vector3f(0, 1, 0);
	Vector3f thirdColumn = Vector3f(-std::sin(radians), 0, std::cos(radians));

	Matrix4x4 rotationMatrix = Matrix4x4(firstColumn, secondColumn, thirdColumn);

	double model[4][4] = {
		{std::cos(radians), 0, std::sin(radians),0 },
		{0, 1, 0 ,0},
		{-std::sin(radians), 0, std::cos(radians),0},
		{0, 0, 0, 1}
	};

	Matrix4x4 modelMatrix = Matrix4x4(model);



	Matrix4x4 mvpMatrix = get_project_matrix(0.1, 50, 75, 1) *
		get_view_matrix(Vector3f(0, 0, 2.))* modelMatrix;

	mvpMatrix.print();

	int screen_width = 1500;
	int screen_height = 1500;

	TGAImage image(screen_width, screen_height, TGAImage::RGB);
	TGAImage imageDepth(screen_width, screen_height, TGAImage::RGB);



	//OBJRenderer::drawTriangleObj("../obj/african_head/african_head.obj",image, mvpMatrix, screen_width, screen_height, imageDepth, red);
	OBJRenderer::drawTriangleObj("../obj/diablo3_pose/diablo3_pose.obj", image, mvpMatrix, screen_width, screen_height,  imageDepth, red);
	//OBJRenderer::drawTriangleObj("../obj/boggie/body.obj", image, imageDepth, red);
	//OBJRenderer::drawTriangleObj("../obj/boggie/eye.obj", image, imageDepth, red);
	//OBJRenderer::drawTriangleObj("../obj/boggie/head.obj", image, imageDepth, red);
	//OBJRenderer::drawObjTriangleDepth("../obj/diablo3_pose/diablo3_pose.obj", imageDepth);

	//Triangle triangle = Triangle(Vector3f(200, 100, 0), Vector3f(50, 400, 0), Vector3f(450, 120, 0));
	//Triangle triangle1 = Triangle(Vector3f(350, 200, 0), Vector3f(130, 310, 0), Vector3f(270, 30, 0));
	//Triangle triangle2 = Triangle(Vector3f(130, 310, 0), Vector3f(100, 200, 0), Vector3f(270, 30, 0));

	// i want to have the origin at the left bottom corner of the image
	//image.flip_vertically();
	image.write_tga_file("output.tga");
	//imageDepth.flip_vertically();
	imageDepth.write_tga_file("outputDepth.tga");

	system("output.tga");

	return 0;
}

