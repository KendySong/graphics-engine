#include <cmath>

#include "Math.hpp"

float Math::dot(const Vec2& vec1, const Vec2& vec2)
{
    return (vec1.x * vec2.y) + (vec1.y * vec2.y);
}

float Math::magnitude(const Vec2& vec1)
{
    return sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
}

Vec2 Math::normalize(Vec2& vec1)
{
    float length = this->magnitude(vec1);
    Vec2 normalized (vec1.x / length, vec2.y / length);
}