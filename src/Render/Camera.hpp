#pragma once
#include "../Math/Vec2.hpp"
#include "../Math/Vec3.hpp"

class Camera
{
public :
	Camera(float speed, float sensitivity);
	void processMovement(float deltatime) noexcept;
	void processRotation() noexcept;

	Vec3& getPosition() noexcept;
	Vec3& getRotation() noexcept;
	Vec3& getDirection() noexcept;
	float& getSensitivity() noexcept;

private :
	Vec3 m_position;
	Vec3 m_rotation;
	Vec3 m_front;
	Vec3 m_up;
	float m_rotationLimit;
	float m_speed;
	float m_sensitivity;

	Vec2 m_mousePos;
	Vec2 m_lastMousePos;
	bool m_firstMovement;
};