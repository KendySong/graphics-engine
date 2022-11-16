#pragma once 
#include "../Render/Triangle.hpp"
#include "../Render/Scene.hpp"
#include "../Render/Graphics.hpp"

class Sandbox 
{
public :
	Sandbox() = default;

	void load();

	void update(float deltaTime);

	void draw(Graphics& graphics);

private :
	Scene m_scene;
	float m_angle;
	Vec3 m_camera;
	std::vector<Triangle> m_toRender;
};