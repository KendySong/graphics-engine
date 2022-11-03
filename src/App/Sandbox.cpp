#include "Sandbox.hpp"

void Sandbox::load()
{
	m_scene.loadModel("../assets/teapot.obj", formatOBJ::fvvv);
	camera = Vec3(0, -2, -4);
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
			p1 = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].a - 1], angle);
			p2 = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].b - 1], angle);
			p3 = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].c - 1], angle);
			p1 += camera;
			p2 += camera;
			p3 += camera;

			Vec3 normal = Math::cross(p2 - p1, p3 - p1);
			Vec3 ray = camera - p1;
			if (Math::dot(normal, ray) > 0)
			{
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
}