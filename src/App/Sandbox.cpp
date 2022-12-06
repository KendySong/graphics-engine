#include <string>
#include <ImGui/imgui.h>

#include "Sandbox.hpp"
#include "../Render/Light/DirectionalLight.hpp"
#include "../Settings.hpp"
#include "../Render/Color.hpp"

void Sandbox::load()
{
	m_light.position = Vec3(0, 0, -1);
	m_light.color = 0xFFFF0000;

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

	aspect = (float)stg::HEIGHT / (float)stg::WIDTH;
	angle = 90;
}

void Sandbox::update(float deltaTime, SDL_Event& event)
{
	m_angle += deltaTime;	
	m_camera->processMovement(deltaTime);
}

void Sandbox::draw(Graphics& graphics)
{
	const Vec3& camPos = m_camera->getPosition();
	const Vec3& camRotation = m_camera->getRotation();

	ImGui::Begin("Camera");
	ImGui::TextUnformatted("Position");
	ImGui::Separator();
	ImGui::Text("X[%f] Y[%f] Z[%f]", m_camera->getPosition().x, m_camera->getPosition().y, m_camera->getPosition().z);

	ImGui::TextUnformatted("Rotation");
	ImGui::Separator();
	ImGui::Text("X[%f] Y[%f] Z[%f]", m_camera->getRotation().x, m_camera->getRotation().y, m_camera->getRotation().z);

	ImGui::TextUnformatted("Direction");
	ImGui::Separator();
	ImGui::Text("X[%f] Y[%f] Z[%f]", m_camera->getDirection().x, m_camera->getDirection().y, m_camera->getDirection().z);
	ImGui::SliderFloat("fov", &angle, 1, 90);
	ImGui::End();

	ImGui::Begin("Light");
	ImGui::Text("Light color : R(%i) G(%i) B(%i)", (m_light.color & 0x00FF0000) >> 16, (m_light.color & 0x0000FF00) >> 8, (m_light.color & 0x000000FF));
	ImGui::SliderFloat("X", &m_light.position.x, 1, 90);
	ImGui::SliderFloat("Y", &m_light.position.y, 1, 90);
	ImGui::SliderFloat("Z", &m_light.position.z, 1, 90);
	ImGui::End();

	std::vector<Mesh>& scene = m_scene.getMeshes();
	for (size_t i = 0; i < scene.size(); i++)
	{
		for (size_t j = 0; j < scene[i].faceIndex.size(); j++)
		{
			const Face& face = scene[i].faceIndex[j];			

			Vec3 p0 = Math::rotateY(scene[i].vertex[face.a - 1], m_angle);
			Vec3 p1 = Math::rotateY(scene[i].vertex[face.b - 1], m_angle);
			Vec3 p2 = Math::rotateY(scene[i].vertex[face.c - 1], m_angle);

			p0 += scene[i].position;
			p1 += scene[i].position;
			p2 += scene[i].position;	

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
					Math::projectPerspective(p0, Math::toRadian(-angle), zNear, zFar, aspect),
					Math::projectPerspective(p1, Math::toRadian(-angle), zNear, zFar, aspect),
					Math::projectPerspective(p2, Math::toRadian(-angle), zNear, zFar, aspect),
					WHITE
				);
			}
		}
	}
	
}