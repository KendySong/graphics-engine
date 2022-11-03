#include "Sandbox.hpp"

void Sandbox::load()
{
	m_scene.loadModel("../assets/teapot.obj");
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
			Vec2 a, b, c;
			Vec3 x, y, z;

			x = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].a - 1], angle);
			y = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].b - 1], angle);
			z = Math::rotateY(sceneMeshes[i].vertex[sceneMeshes[i].faceIndex[j].c - 1], angle);

			x.z -= 4;
			y.z -= 4;
			z.z -= 4;

			a = Math::projectPerspective(x);
			b = Math::projectPerspective(y);
			c = Math::projectPerspective(z);

			graphics.drawTriangle
			(
				a,
				b,
				c,
				0xFF00FF00
			);
		}
	}
}