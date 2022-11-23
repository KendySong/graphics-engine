#include <string>
#include <ImGui/imgui.h>

#include "Sandbox.hpp"
#include "../Settings.hpp"

void Sandbox::load()
{
	m_scene.loadModel("../assets/teapot.obj", formatOBJ::fvvv);
	m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(0, -1, 5);

	m_scene.loadModel("../assets/cube.obj", formatOBJ::fvtn);
	m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(4.5, 0, 5.5);

	m_scene.loadModel("../assets/f22.obj", formatOBJ::fvtn);
	m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(-4.5, 0, 5.5);

	m_angle = 0;
	m_camera = Vec3(0, 0, 0);

	aspect = (float)stg::HEIGHT / (float)stg::WIDTH;
	angle = 90;
	zNear = 0.1f;
	zFar = 100;
}

void Sandbox::update(float deltaTime)
{
	m_angle += deltaTime;	
}

void Sandbox::draw(Graphics& graphics)
{
	ImGui::Begin("Camera");
	ImGui::SliderFloat("Angle", &angle, 1, 90);
	ImGui::SliderFloat("zNear", &zNear, 0.0, 20);
	ImGui::SliderFloat("zFar", &zFar, 1, 1000);
	ImGui::End();

	std::vector<Mesh>& scene = m_scene.getMeshes();
	for (size_t i = 0; i < scene.size(); i++)
	{
		std::string name = "Transform[" + std::to_string(i) + "]";
		ImGui::Begin(name.c_str());
		ImGui::InputFloat("X", &scene[i].position.x);
		ImGui::InputFloat("Y", &scene[i].position.y);
		ImGui::InputFloat("Z", &scene[i].position.z);
		ImGui::End();

		for (size_t j = 0; j < scene[i].faceIndex.size(); j++)
		{
			Face& face = scene[i].faceIndex[j];
			Vec3 p0 = Math::rotateY(scene[i].vertex[face.a - 1], m_angle);
			Vec3 p1 = Math::rotateY(scene[i].vertex[face.b - 1], m_angle);
			Vec3 p2 = Math::rotateY(scene[i].vertex[face.c - 1], m_angle);

			p0 += scene[i].position;
			p1 += scene[i].position;
			p2 += scene[i].position;

			graphics.drawTriangle
			(
				Math::projectPerspective(p0, Math::toRadian(-angle), zNear, zFar, aspect),
				Math::projectPerspective(p1, Math::toRadian(-angle), zNear, zFar, aspect),
				Math::projectPerspective(p2, Math::toRadian(-angle), zNear, zFar, aspect),
				0xFFAA00FF
			);

			/*
			if (graphics.cullFace(p0, p1, p2, m_camera))
			{	
				
				graphics.drawFilledTriangle
				(
					Math::projectPerspective(p0),
					Math::projectPerspective(p1),
					Math::projectPerspective(p2),
					0xFFFFFFFF
				);				

							
			}
			*/
			
		}
	}
	
}