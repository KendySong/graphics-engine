#pragma once

#include <vector>

#include "Face.hpp"
#include "../Math/Vec3.hpp"

struct Mesh 
{
	std::vector<Vec3> vertex;
	std::vector<Face> faceIndex;
};