#pragma once
#include "Vec2.hpp"
#include "Vec3.hpp"

class Mat4
{
public :
    Mat4() = default;
    Mat4(float init);

    float m[4][4] = {0};
};

Mat4 operator*(const Mat4& m1, const Mat4& m2);