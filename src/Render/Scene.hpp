#pragma once
#include "Mesh.hpp"
#include "formatOBJ.hpp"

class Scene 
{
public :
	Scene() = default;

	void loadModel(const char* path, formatOBJ type);

	std::vector<Mesh>& getMeshes() noexcept;

private :
	std::vector<Mesh> m_meshes;
};