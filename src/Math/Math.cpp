#define _USE_MATH_DEFINES
#include <cmath>

#include "Math.hpp"
#include "../Settings.hpp"

float Math::dot(const Vec2& vec1, const Vec2& vec2) noexcept
{
    return (vec1.x * vec2.y) + (vec1.y * vec2.y);
}

float Math::magnitude(const Vec2& vec) noexcept
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

Vec2 Math::normalize(const Vec2 & vec) noexcept
{
    float length = Math::magnitude(vec);
    return vec / length;
}

Vec3 Math::cross(const Vec3& vec1, const Vec3& vec2) noexcept
{
    return 
    {
        vec1.y * vec2.z - vec1.z * vec2.y, 
        vec1.z * vec2.x - vec1.x * vec2.z, 
        vec1.x * vec2.y - vec1.y * vec2.x 
    };
}

float Math::dot(const Vec3& vec1, const Vec3& vec2) noexcept
{
    return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
}

float Math::magnitude(const Vec3 & vec) noexcept
{
    return sqrt(vec.x * vec.x + vec.z * vec.z + vec.y * vec.y);
}

Vec3 Math::normalize(const Vec3& vec) noexcept
{
    float length = Math::magnitude(vec);
    return vec / length;
}

Vec3 Math::rotateX(const Vec3& vec, float angle)
{
    angle += atan2f(vec.y, vec.z);
    float length = Math::magnitude({ vec.y, vec.z });

    Vec3 rotated
    {
        vec.x,
        length * sin(angle),
        length * cos(angle)
    };
    return rotated;
}

Vec3 Math::rotateY(const Vec3& vec, float angle)
{
    angle += atan2(vec.z, vec.x);
    float length = Math::magnitude({ vec.x, vec.z });

    Vec3 rotated
    {
        length * sin(angle),
        vec.y,
        length * cos(angle)
    };
    return rotated;
}

Vec3 Math::rotateZ(const Vec3& vec, float angle)
{
    angle += atan2f(vec.y, vec.x);
    float length = Math::magnitude({ vec.x, vec.y });

    Vec3 rotated
    {
        length * sin(angle),
        length * cos(angle),
        vec.z
    };
    return rotated;  
}

Mat4 Math::identity() noexcept
{
    Mat4 mat4(0);
    mat4.m[0][0] = 1;
    mat4.m[1][1] = 1;
    mat4.m[2][2] = 1;
    mat4.m[3][3] = 1;
    return mat4;
}

Vec2 Math::projectPerspective(Vec3& pos, float angle, float zNear, float zFar, float aspect)
{
    float fov = 1 / tan(angle / 2);
    pos.x *= fov * aspect;
    pos.y *= fov;

    return Vec2
    {
        (pos.x * stg::HALF_WIDTH / pos.z) + stg::HALF_WIDTH,
        (pos.y * stg::HALF_HEIGHT / pos.z) + stg::HALF_HEIGHT
    };
}

Vec2 Math::projectOrthographic(const Vec3& pos)
{
    return Vec2(pos.x, pos.y);
}

float Math::toRadian(float angle)
{
    return angle * (M_PI / 180);
}