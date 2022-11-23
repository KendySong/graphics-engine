#include "Mat4.hpp"
#include "Math.hpp"

Mat4::Mat4(float init)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m[i][j] = init;
		}
	}
}

Mat4 operator*(const Mat4& m1, const Mat4& m2)
{
	Vec2 index;
	Mat4 mat4;
	float dot = 0;

	for (size_t y = 0; y < 4; y++)
	{	
		for (size_t x = 0; x < 4; x++)
		{
			dot = 0;
			for (size_t i = 0; i < 4; i++)
			{
				dot += m1.m[y][i] * m2.m[i][x];
			}
			mat4.m[y][x] = dot;
		}
	}
	return mat4;
}