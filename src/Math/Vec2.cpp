#include "Vec2.hpp"

Vec2::Vec2()
{
    x = 0;
    y = 0;
}

Vec2::Vec2(float x, float y)
{
    x = x;
    y = y;
}

void Vec2::operator+=(const Vec2& vec) noexcept
{
    this->x += vec.x;
    this->y += vec.y;
}

void Vec2::operator-=(const Vec2& vec) noexcept
{
    this->x -= vec.x;
    this->y -= vec.y;
}

void Vec2::operator*=(const Vec2& vec) noexcept
{
    this->x *= vec.x;
    this->y *= vec.y;
}

void Vec2::operator/=(const Vec2& vec) noexcept
{
    this->x /= vec.x;
    this->y /= vec.y;
}

Vec2 operator+(const Vec2& vec1, const Vec2& vec2)
{
    return {vec1.x + vec2.x, vec1.y + vec2.y};
}

Vec2 operator-(const Vec2& vec1, const Vec2& vec2)
{
    return {vec1.x - vec2.x, vec1.y - vec2.y};
}

Vec2 operator*(const Vec2& vec1, const Vec2& vec2)
{
    return {vec1.x * vec2.x, vec1.y * vec2.y};
}

Vec2 operator/(const Vec2& vec1, const Vec2& vec2)
{
    return {vec1.x / vec2.x, vec1.y / vec2.y};
}

bool operator==(Vec2& vec1, Vec2& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y;
}