#pragma once 
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

	Vec3 pos;
	float angle = 0;
};