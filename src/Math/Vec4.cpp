#include "Vec4.hpp"

Vec4::Vec4()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = w;
}

Vec4::Vec4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vec4::operator+=(const Vec4& vec) noexcept
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
    this->w += vec.w;
}

void Vec4::operator-=(const Vec4& vec) noexcept
{
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    this->w -= vec.w;
}

void Vec4::operator*=(const Vec4& vec) noexcept
{
    this->x *= vec.x;
    this->y *= vec.y;
    this->z *= vec.z;
    this->w *= vec.w;
}

void Vec4::operator*=(float scalar) noexcept
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w += scalar;
}

void Vec4::operator/=(const Vec4& vec) noexcept
{
    this->x /= vec.x;
    this->y /= vec.y;
    this->z /= vec.z;
    this->w /= vec.w;
}

Vec4 operator+(const Vec4& vec1, const Vec4& vec2) noexcept
{
    return { vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z , vec1.w + vec2.w};
}

Vec4 operator-(const Vec4& vec1, const Vec4& vec2) noexcept
{
    return { vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w};
}

Vec4 operator*(const Vec4& vec1, const Vec4& vec2) noexcept
{
    return { vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w };
}

Vec4 operator/(const Vec4& vec1, const Vec4& vec2) noexcept
{
    return { vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w };
}

Vec4 operator/(const Vec4& vec, float scalar) noexcept
{
    return { vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar };
}

bool operator==(Vec4& vec1, Vec4& vec2) noexcept
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
}
