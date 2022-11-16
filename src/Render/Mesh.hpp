#pragma once

#include <vector>

#include "Face.hpp"
#include "../Math/Vec3.hpp"

struct Mesh 
{
	//Model
	std::vector<Vec3> vertex;
	std::vector<Face> faceIndex;

	//Transform
	Vec3 position;
	Vec3 rotation;
	Vec3 scale;
};