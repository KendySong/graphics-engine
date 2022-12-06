#pragma once 
#include "../Render/Triangle.hpp"
#include "../Render/Scene.hpp"
#include "../Render/Graphics.hpp"
#include "../Render/Camera.hpp"

class Sandbox 
{
public :
	Sandbox() = default;

	void load();

	void update(float deltaTime, SDL_Event& event);

	void draw(Graphics& graphics);

private :
	Scene m_scene;
	float m_angle;

	Camera* m_camera;
	float aspect;
};