#include <ImGui/imgui.h>

#include "Sandbox.hpp"

void Sandbox::load()
{
	//m_scene.loadModel("../assets/teapot.obj", formatOBJ::fvvv);
	m_scene.loadModel("../assets/cube.obj", formatOBJ::fvtn);

	camera = Vec3(0, 0, -3);
}

void Sandbox::update(float deltaTime)
{
	angle += deltaTime;
}

void Sandbox::draw(Graphics& graphics)
{
	std::vector<Mesh>& sceneMeshes = m_scene.getMeshes();
	for (size_t i = 0; i < sceneMeshes.size(); i++)
	{
		for (size_t j = 0; j < sceneMeshes[i].faceIndex.size(); j++)
		{
			Vec3 p1, p2, p3;
			p1 = sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].a - 1];
			p2 = sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].b - 1];
			p3 = sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].c - 1];

			p1 = Math::rotateY(p1, angle);
			p2 = Math::rotateY(p2, angle);
			p3 = Math::rotateY(p3, angle);		
			
			Vec3 normal = Math::cross(p2 - p1, p3 - p1);
			Vec3 ray = p1 - camera;
			if (Math::dot(normal, camera) > 0)
			{
				p1 += camera;
				p2 += camera;
				p3 += camera;

				//Project and draw
				graphics.drawTriangle
				(
					Math::projectPerspective(p1),
					Math::projectPerspective(p2),
					Math::projectPerspective(p3),
					0xFF00FF00
				);
			}
			
		}
	}

	ImGui::Begin("test");
	ImGui::End();
}