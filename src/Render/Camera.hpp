#pragma once
#include "../Math/Vec3.hpp"

class Camera
{
public :
	Camera(float speed, float sensitivity);
	void processMovement(float deltatime) noexcept;

	Vec3& getPosition() noexcept;

private :
	Vec3 m_position;
	float m_speed;
};