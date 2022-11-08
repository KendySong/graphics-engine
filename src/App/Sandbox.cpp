#include <ImGui/imgui.h>

#include "Sandbox.hpp"

void Sandbox::load()
{
	//m_scene.loadModel("../assets/teapot.obj", formatOBJ::fvvv);
	m_scene.loadModel("../assets/cube.obj", formatOBJ::fvtn);

	camera = Vec3(0, 0, 3);
	cull = true;
}

void Sandbox::update(float deltaTime)
{
	angle += deltaTime;
}

void Sandbox::draw(Graphics& graphics)
{
	//graphics.drawTriangle(Vec2(640, 60), Vec2(320, 360), Vec2(700, 600), 0xFF00FF00);
	//graphics.drawFilledTriangle(Vec2(640, 60), Vec2(320, 360), Vec2(700, 600), 0xFF00FF00);

	
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
				
			p1 = Math::rotateX(p1, angle);
			p2 = Math::rotateX(p2, angle);
			p3 = Math::rotateX(p3, angle);

			if (cull) 
			{
				if (graphics.cullFace(p1, p2, p3, camera))
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
			else 
			{
				p1 += camera;
				p2 += camera;
				p3 += camera;

				//Project and draw
				graphics.drawFilledTriangle
				(
					Math::projectPerspective(p1),
					Math::projectPerspective(p2),
					Math::projectPerspective(p3),
					0xFF00FF00
				);			
			}
				
		}
	}

	ImGui::Begin("Transform");
		ImGui::SliderFloat("X", &camera.x, -10, 10);
		ImGui::SliderFloat("Y", &camera.y, -10, 10);
		ImGui::SliderFloat("Z", &camera.z, -10, 10);
		ImGui::Checkbox("Cull", &cull);
	ImGui::End();
	
}