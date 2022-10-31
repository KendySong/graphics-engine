#pragma once
#include "Vec2.hpp"

class Math
{
public :
    static float dot(const Vec2& vec1, const Vec2& vec2);
    static float magnitude(const Vec2& vec1);
    static Vec2 normalize(const Vec2& vec1);
};