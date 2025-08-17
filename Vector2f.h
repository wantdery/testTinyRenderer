#pragma once
#include <cassert>
#include <cmath>

class Vector2f
{
public:

	Vector2f(float x, float y)
		:x(x), y(y)
	{
	}

	Vector2f()
		:x(0), y(0)
	{
	}

	Vector2f operator+(const Vector2f& v)
	{
		return Vector2f(x + v.x, y + v.y);
	}

	Vector2f operator-(const Vector2f& v)
	{
		return Vector2f(x - v.x, y - v.y);
	}

	Vector2f operator*(float s)
	{
		return Vector2f(x * s, y * s);
	}

	float dot(const Vector2f& v)
	{
		return x * v.x + y * v.y;
	}

	float operator[](int i)
	{
		if (i > 1)
		{
			assert("over the limit!");
		}

		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		}
	}



	Vector2f normalize()
	{
		float length = std::sqrt(x * x + y * y);
		return Vector2f(x / length, y / length);
	}

	float norm()
	{
		return std::sqrt(x * x + y * y);

	}

	float x, y;

private:

};

