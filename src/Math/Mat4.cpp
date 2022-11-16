#include "Mat4.hpp"
#include "Math.hpp"

Mat4::Mat4()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat[i][j] = 0;
		}
	}
}

Mat4::Mat4(float init)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			mat[i][j] = init;
		}
	}
}