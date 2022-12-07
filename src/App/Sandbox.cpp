#include <string>
#include <ImGui/imgui.h>

#include "Sandbox.hpp"
#include "../Render/Light/DirectionalLight.hpp"
#include "../Settings.hpp"
#include "../Render/Color.hpp"

void Sandbox::load()
{
	//Model loading
	m_scene.loadModel("../assets/teapot.obj", formatOBJ::fvvv);
	m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(0, -1, 5);

	m_scene.loadModel("../assets/cube.obj", formatOBJ::fvtn);
	m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(4.5, 0, 5.5);

	m_scene.loadModel("../assets/f22.obj", formatOBJ::fvtn);
	m_scene.getMeshes()[m_scene.getMeshes().size() - 1].position = Vec3(-4.5, 0, 5.5);	

	//Camera
	m_angle = 0;
	m_camera = new Camera(10, 1);

	//Projection
	aspect = (float)stg::HEIGHT / (float)stg::WIDTH;
}

void Sandbox::update(float deltaTime, SDL_Event& event)
{
	m_angle += deltaTime;	
	m_camera->processMovement(deltaTime);
}

void Sandbox::draw(Graphics& graphics)
{
	Vec3& camPos = m_camera->getPosition();
	Vec3& camRotation = m_camera->getRotation();

	ImGui::Begin("Camera");
	ImGui::TextUnformatted("Transform");
	ImGui::Separator();

	ImGui::TextUnformatted("Position");
	ImGui::SameLine();
	ImGui::PushItemWidth(175);
	ImGui::InputFloat3("[X][Y][Z]", &camPos.x);

	ImGui::TextUnformatted("Rotation");
	ImGui::SameLine();
	ImGui::InputFloat3("[X][Y][Z]", &camRotation.x);
	ImGui::PopItemWidth();
	ImGui::Separator();

	ImGui::InputFloat("fov", &stg::fov);
	ImGui::InputFloat("sensitivity", &m_camera->getSensitivity());
	ImGui::End();

	std::vector<Mesh>& scene = m_scene.getMeshes();
	for (size_t i = 0; i < scene.size(); i++)
	{
		for (size_t j = 0; j < scene[i].faceIndex.size(); j++)
		{
			//World space
			const Face& face = scene[i].faceIndex[j];			
			Vec3 p0 = Math::rotateY(scene[i].vertex[face.a - 1], m_angle);
			Vec3 p1 = Math::rotateY(scene[i].vertex[face.b - 1], m_angle);
			Vec3 p2 = Math::rotateY(scene[i].vertex[face.c - 1], m_angle);
			p0 += scene[i].position;
			p1 += scene[i].position;
			p2 += scene[i].position;	

			//View space
			p0 -= camPos;
			p1 -= camPos;
			p2 -= camPos;
			p0 = Math::rotateY(p0, camRotation.y);
			p1 = Math::rotateY(p1, camRotation.y);
			p2 = Math::rotateY(p2, camRotation.y);
			p0 = Math::rotateX(p0, camRotation.x);
			p1 = Math::rotateX(p1, camRotation.x);
			p2 = Math::rotateX(p2, camRotation.x);

			if (graphics.cullFace(p0, p1, p2, camPos))
			{
				graphics.drawTriangle
				(
					Math::projectPerspective(p0, Math::toRadian(-stg::fov), aspect),
					Math::projectPerspective(p1, Math::toRadian(-stg::fov), aspect),
					Math::projectPerspective(p2, Math::toRadian(-stg::fov), aspect),
					WHITE
				);
			}
		}
	}
	
}