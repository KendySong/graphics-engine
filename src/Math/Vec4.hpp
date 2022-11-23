#pragma once
class Vec4
{
public:
    Vec4();

    Vec4(float x, float y, float z, float w);

    void operator+=(const Vec4& vec) noexcept;
    void operator-=(const Vec4& vec) noexcept;
    void operator*=(const Vec4& vec) noexcept;
    void operator*=(float scalar) noexcept;
    void operator/=(const Vec4& vec) noexcept;

    float x;
    float y;
    float z;
    float w;
};

Vec4 operator+(const Vec4& vec1, const Vec4& vec2) noexcept;

Vec4 operator-(const Vec4& vec1, const Vec4& vec2) noexcept;

Vec4 operator*(const Vec4& vec1, const Vec4& vec2) noexcept;

Vec4 operator/(const Vec4& vec1, const Vec4& vec2) noexcept;

Vec4 operator/(const Vec4& vec, float scalar) noexcept;

bool operator==(Vec4& vec1, Vec4& vec2) noexcept;