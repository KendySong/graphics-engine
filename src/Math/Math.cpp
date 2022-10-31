#include <cmath>

#include "Math.hpp"

float Math::dot(const Vec2& vec1, const Vec2& vec2) noexcept
{
    return (vec1.x * vec2.y) + (vec1.y * vec2.y);
}

float Math::magnitude(const Vec2& vec) noexcept
{
    return sqrt(vec1.x * vec1.x + vec1.y * vec1.y);
}

Vec2 Math::normalize(Vec2& vec) noexcept
{
    float length = this->magnitude(vec1);
    return vec / length;
}

Vec3 cross(const Vec3& vec1, const Vec3& vec2)
{
    Vec3 cross;
    cross.x = vec1.y * vec2.z - vec1.z * vec2.y;
    cross.y = vec1.z * vec2.x - vec1.x * vec2.z;
    cross.z = vec1.x * vec2.y - vec1.y * vec2.x;
    return cross;
}

float dot(const Vec2& vec1, const Vec2& vec2)
{
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

float magnitude(const Vec3& vec)
{
    return sqrt(vec.x * vec.x + vec.z * vec.z + vec.y * vec.y);
}

Vec3 normalize(const Vec3& vec)
{
    float length = this->magnitude(vec);
    return vec / length;
}