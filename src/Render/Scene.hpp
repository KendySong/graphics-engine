#pragma once
#include "Mesh.hpp"

class Scene 
{
public :
	Scene() = default;

	void loadModel(const char* path);

	std::vector<Mesh>& getMeshes() noexcept;

private :
	std::vector<Mesh> m_meshes;
};