#pragma once
#include <iomanip>
#include <iostream>

#include "Vector3f.h"
#include "Vector4f.h"

class Matrix4x4
{
public:
	Matrix4x4() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j)
			{
				data[i][j] = 0.0;
			}
		}
	};
	// 构造函数：使用二维数组初始化
	Matrix4x4(double init[4][4]) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j)
			{
				data[i][j] = init[i][j];
			}
		}
	}

	static Matrix4x4 identity()
	{
		double identity[4][4] = {
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,0,1}
		};

		return Matrix4x4(identity);
	}

	Matrix4x4(Vector3f a, Vector3f b, Vector3f c) {
		Matrix4x4 identity = Matrix4x4();

		identity.data[0][0] = a.x;
		identity.data[0][1] = a.y;
		identity.data[0][2] = a.z;
		identity.data[1][0] = b.x;
		identity.data[1][1] = b.y;
		identity.data[1][2] = b.z;
		identity.data[2][0] = c.x;
		identity.data[2][1] = c.y;
		identity.data[2][2] = c.z;

		*this = identity;
	}

	// 打印矩阵
	void print() const {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j)
			{
				std::cout << std::setw(8) << data[i][j] << " ";
			}
			std::cout << '\n';
		}
	}

	Matrix4x4 operator*(const Matrix4x4& other)
	{
		Matrix4x4 result;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 4; ++k)
				{
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}

		return result;
	}

	Vector3f operator*(const Vector3f& v)
	{
		Vector3f result;
		result.x = data[0][0] * v.x + data[1][0] * v.y + data[2][0] * v.z;
		result.y = data[0][1] * v.x + data[1][1] * v.y + data[2][1] * v.z;
		result.z = data[0][2] * v.x + data[0][2] * v.y + data[2][2] * v.z;
		return result;
	}

	Vector4f operator*(const Vector4f& v)
	{
		Vector4f result;
		//result.x = data[0][0] * v.x + data[1][0] * v.y + data[2][0] * v.z + data[3][0] * v.w;
		//result.y = data[0][1] * v.x + data[1][1] * v.y + data[2][1] * v.z + data[3][1] * v.w;
		//result.z = data[0][2] * v.x + data[0][2] * v.y + data[2][2] * v.z + data[3][2] * v.w;
		//result.w = data[0][3] * v.x + data[0][3] * v.y + data[2][3] * v.z + data[3][3] * v.w;

		for (int i = 0; i < 4; ++i)
		{
			float a = 0;
			for (int j = 0; j < 4; ++j)
			{
				a += data[i][j] * v[j];
			}
			result[i] = a;
		}
		return result;
	}


private:
	double data[4][4];
};

