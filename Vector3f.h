#pragma once
#include <assert.h>
#include <cmath>
#include <iostream>
#include <ostream>

class Vector3f
{
public:

	Vector3f(float x, float y, float z)
		:x(x), y(y), z(z)
	{
	}

	Vector3f()
		:x(0), y(0), z(0)
	{
	}

	Vector3f operator+(const Vector3f& v)
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(const Vector3f& v)
	{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float s)
	{
		return Vector3f(x * s, y * s, z * s);
	}

	float dot(const Vector3f& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	void print()
	{
		std::cout << x << " " << y << " " << z << std::endl;
	}


	float operator[](int i)
	{
		if (i>2)
		{
			assert("over the limit!");
		}

		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	Vector3f cross(const Vector3f& v)
	{
		return Vector3f(
			this->y * v.z - this->z * v.y,
			this->z * v.x - this->x * v.z,
			this->x * v.y - this->y * v.x);
	}

    Vector3f normalize()
	{
		float length = std::sqrt(x * x + y * y + z * z);
		return Vector3f(x / length, y / length, z / length);
	}

	float norm()
	{
		return std::sqrt(x * x + y * y + z * z);
		 
	}

	float x, y, z;

private:
	
};

