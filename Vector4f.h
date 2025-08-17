#pragma once
#include <cassert>
#include <cmath>

#include "Vector3f.h"

class Vector4f
{
public:

	Vector4f(float x, float y, float z, float w)
		:x(x), y(y), z(z), w(w)
	{
	}

	Vector4f()
		:x(0), y(0), z(0), w(0)
	{
	}

	Vector4f(Vector3f src, float w)
	{
		x = src.x;
		y = src.y;
		z = src.z;
		w = 0;
	}

	Vector4f operator+(const Vector4f& v)
	{
		return Vector4f(x + v.x, y + v.y, z + v.z, w);
	}

	Vector4f operator-(const Vector4f& v)
	{
		return Vector4f(x - v.x, y - v.y, z - v.z, w);
	}

	Vector4f operator*(float s)
	{
		return Vector4f(x * s, y * s, z * s, w * s);
	}

	float dot(const Vector4f& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	// 修改非 const 版本的 operator[] 返回引用
	float& operator[](int i)
	{
		if (i > 3 || i < 0)  // 增加边界检查
		{
			assert("over the limit!");
		}

		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: assert("over the limit!"); return x; // 防止编译器警告
		}
	}

	// 保留 const 版本用于 const 对象
	const float& operator[](int i) const
	{
		if (i > 3 || i < 0)
		{
			assert("over the limit!");
		}

		switch (i)
		{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
		default: assert("over the limit!"); return x; // 防止编译器警告
		}
	}

	//float operator[](int i) const
	//{
	//	if (i > 3)
	//	{
	//		assert("over the limit!");
	//	}

	//	switch (i)
	//	{
	//	case 0:return x;
	//	case 1:return y;
	//	case 2:return z;
	//	case 3:return w;
	//	}
	//}

	Vector4f cross(const Vector4f& v)
	{
		return Vector4f(
			this->y * v.z - this->z * v.y,
			this->z * v.x - this->x * v.z,
			this->x * v.y - this->y * v.x,
			w);
	}

	Vector4f normalize()
	{
		float length = std::sqrt(x * x + y * y + z * z + w * w);
		return Vector4f(x / length, y / length, z / length, w);
	}

	float norm()
	{
		return std::sqrt(x * x + y * y + z * z + w * w);

	}

	float x, y, z, w;

private:

};

