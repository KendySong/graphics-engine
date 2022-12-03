#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() 
{
	color = 0;
}

DirectionalLight::DirectionalLight(Vec3 position, std::uint32_t color)
{
	this->position = position;
	this->color = color;
}