#include <windows.h>
#include <iostream>
#include <SDL/SDL.h>

#include "Camera.hpp"

Camera::Camera(float speed, float sensitivity) 
{
	m_speed = speed;
}

void Camera::processMovement(float deltatime) noexcept
{
	if (GetAsyncKeyState(87) == -32768)
	{
		m_position.z -= deltatime * m_speed;
	}

	if (GetAsyncKeyState(65) == -32768)
	{
		m_position.x -= deltatime * m_speed;
	}

	if (GetAsyncKeyState(83) == -32768)
	{
		m_position.z += deltatime * m_speed;
	}

	if (GetAsyncKeyState(68) == -32768)
	{
		m_position.x += deltatime * m_speed;
	}

	if (GetAsyncKeyState(32) == -32768)
	{
		m_position.y += deltatime * m_speed;
	}

	if (GetAsyncKeyState(VK_SHIFT) == -32768)
	{
		m_position.y -= deltatime * m_speed;
	}
}

Vec3& Camera::getPosition() noexcept
{
	return m_position;
}