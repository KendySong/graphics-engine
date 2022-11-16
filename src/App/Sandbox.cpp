#include <ImGui/imgui.h>

#include "Sandbox.hpp"

void Sandbox::load()
{
	m_scene.loadModel("../assets/teapot.obj", formatOBJ::fvvv);
	m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(0, 0, 3.5);

	//m_scene.loadModel("../assets/f22.obj", formatOBJ::fvtn);
	//m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(0, 0, 3.5);

	m_angle = 0;
	m_camera = Vec3(0, 0, 0);
}

void Sandbox::update(float deltaTime)
{
	m_angle += deltaTime;	
}

void Sandbox::draw(Graphics& graphics)
{
	std::vector<Mesh>& scene = m_scene.getMeshes();
	for (size_t i = 0; i < scene.size(); i++)
	{
		for (size_t j = 0; j < scene[i].faceIndex.size(); j++)
		{
			Face& face = scene[i].faceIndex[j];

			Vec3 p0 = Math::rotateY(scene[i].vertex[face.a - 1], m_angle);
			Vec3 p1 = Math::rotateY(scene[i].vertex[face.b - 1], m_angle);
			Vec3 p2 = Math::rotateY(scene[i].vertex[face.c - 1], m_angle);

			p0 += scene[i].position;
			p1 += scene[i].position;
			p2 += scene[i].position;

			if (graphics.cullFace(p0, p1, p2, m_camera))
			{
				m_toRender.emplace_back(Math::projectPerspective(p0), Math::projectPerspective(p1), Math::projectPerspective(p2));
			}
		}
	}

	for (size_t i = 0; i < m_toRender.size(); i++)
	{
		graphics.drawTriangle(
			m_toRender[i].a,
			m_toRender[i].b,
			m_toRender[i].c,
			0xFF00FF00
		);
	}
	m_toRender.clear();
}