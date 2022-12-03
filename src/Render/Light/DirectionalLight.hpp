#pragma once
#include <cstdint>
#include "../../Math/Vec3.hpp"

struct DirectionalLight
{
public :
	DirectionalLight();

	DirectionalLight(Vec3 position, std::uint32_t color);

	Vec3 position;
	std::uint32_t color;
};