#include <windows.h>
#include <SDL/SDL.h>

#include "Camera.hpp"
#include "../Math/Math.hpp"

Camera::Camera(float speed, float sensitivity) 
{
	m_speed = speed;
	m_sensitivity = sensitivity;
	m_up = Vec3(0, 1, 0);
	m_front = Vec3(0, 0, 1);
}

void Camera::processMovement(float deltatime) noexcept
{
	
	//W
	if (GetAsyncKeyState(87) == -32768)
	{
		m_position -= m_front * deltatime * m_speed;
	}

	//A
	if (GetAsyncKeyState(65) == -32768)
	{
		m_position.x -= deltatime * m_speed;
	}

	//S
	if (GetAsyncKeyState(83) == -32768)
	{
		m_position += m_front * deltatime * m_speed;
	}

	//D
	if (GetAsyncKeyState(68) == -32768)
	{
		m_position.x += deltatime * m_speed;
	}

	//Space
	if (GetAsyncKeyState(32) == -32768)
	{
		m_position.y -= deltatime * m_speed;
	}

	//Shift
	if (GetAsyncKeyState(VK_SHIFT) == -32768)
	{
		m_position.y += deltatime * m_speed;
	}

	if (GetAsyncKeyState(VK_LEFT) == -32768)
	{

		m_rotation.y += deltatime * m_sensitivity;
	}

	if (GetAsyncKeyState(VK_RIGHT) == -32768)
	{
		m_rotation.y -= deltatime * m_sensitivity;
	}

	if (GetAsyncKeyState(VK_UP) == -32768)
	{
		m_rotation.x -= deltatime * m_sensitivity;
	}

	if (GetAsyncKeyState(VK_DOWN) == -32768)
	{
		m_rotation.x += deltatime * m_sensitivity;
	}

	/* m_position += m_front;
	//W
	if (GetAsyncKeyState(87) == -32768)
	{
		m_position.z -= deltatime * m_speed;
	}

	//A
	if (GetAsyncKeyState(65) == -32768)
	{
		m_position.x -= deltatime * m_speed;
	}

	//S
	if (GetAsyncKeyState(83) == -32768)
	{
		m_position.z += deltatime * m_speed;
	}

	//D
	if (GetAsyncKeyState(68) == -32768)
	{
		m_position.x += deltatime * m_speed;
	}

	//Space
	if (GetAsyncKeyState(32) == -32768)
	{
		m_position.y -= deltatime * m_speed;
	}

	//Shift
	if (GetAsyncKeyState(VK_SHIFT) == -32768)
	{
		m_position.y += deltatime * m_speed;
	}

	if (GetAsyncKeyState(VK_LEFT) == -32768)
	{

		m_rotation.y += deltatime * m_sensitivity;
	}

	if (GetAsyncKeyState(VK_RIGHT) == -32768)
	{
		m_rotation.y -= deltatime * m_sensitivity;
	}

	if (GetAsyncKeyState(VK_UP) == -32768)
	{
		m_rotation.x -= deltatime * m_sensitivity;
	}

	if (GetAsyncKeyState(VK_DOWN) == -32768)
	{
		m_rotation.x += deltatime * m_sensitivity;
	}
	*/
}

Vec3& Camera::getPosition() noexcept
{
	return m_position;
}

Vec3& Camera::getRotation() noexcept
{
	return m_rotation;
}