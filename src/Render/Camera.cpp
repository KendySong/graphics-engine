#include <windows.h>
#include <iostream>
#include <SDL/SDL.h>

#include "Camera.hpp"
#include "../Settings.hpp"
#include "../Math/Math.hpp"

Camera::Camera(float speed, float sensitivity) 
{
	m_speed = speed;
	m_sensitivity = sensitivity;
	m_up = Vec3(0, 1, 0);
	m_front = Vec3(0, 0, 1);

	m_rotationLimit = Math::toRadian(90);

	m_firstMovement = true;
}

void Camera::processMovement(float deltatime) noexcept
{
	//W
	if (GetAsyncKeyState(87) == -32768)
	{
		m_position += m_front * deltatime * m_speed;
	}

	//A
	if (GetAsyncKeyState(65) == -32768)
	{
		m_position -= Math::cross(m_front, m_up) * deltatime * m_speed;
	}

	//S
	if (GetAsyncKeyState(83) == -32768)
	{
		m_position -= m_front * deltatime * m_speed;
	}

	//D
	if (GetAsyncKeyState(68) == -32768)
	{
		m_position += Math::cross(m_front, m_up) * deltatime * m_speed;
	}

	//Space
	if (GetAsyncKeyState(32) == -32768)
	{
		m_position.y += deltatime * m_speed;
	}

	//Shift
	if (GetAsyncKeyState(VK_SHIFT) == -32768)
	{
		m_position.y -= deltatime * m_speed;
	}

	this->processRotation();
}

void Camera::processRotation() noexcept
{
	if (m_rotation.x > m_rotationLimit)
	{
		m_rotation.x = m_rotationLimit;
	}

	if (m_rotation.x < -m_rotationLimit)
	{
		m_rotation.x = -m_rotationLimit;
	}

	if (m_firstMovement)
	{
		m_lastMousePos.x = stg::HALF_WIDTH;
		m_lastMousePos.y = stg::HALF_HEIGHT;
		m_firstMovement = false;
	}

	int x, y;
	SDL_GetMouseState(&x, &y);

	Vec2 mousePos(x, y);
	Vec2 offset = mousePos - m_lastMousePos;
	m_rotation.y -= offset.x * m_sensitivity;
	m_rotation.x += offset.y * m_sensitivity;

	m_front.x = sin(m_rotation.y) * cos(m_rotation.x);
	m_front.y = sin(-m_rotation.x);
	m_front.z = cos(m_rotation.y) * cos(m_rotation.x);

	m_front = Math::normalize(m_front);
}

Vec3& Camera::getPosition() noexcept
{
	return m_position;
}

Vec3& Camera::getRotation() noexcept
{
	return m_rotation;
}

Vec3& Camera::getDirection() noexcept
{
	return m_front;
}

float& Camera::getSensitivity() noexcept 
{
	return m_sensitivity;
}