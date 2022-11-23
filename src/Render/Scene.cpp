#include <string>
#include <fstream>
#include <stdexcept>

#include "Scene.hpp"

void Scene::loadModel(const char* path, formatOBJ type)
{
	std::ifstream fileReader(path);
	if (fileReader.is_open())
	{
		std::string currentLine;
		m_meshes.emplace_back();
		int lastIndex = m_meshes.size() - 1;

		while (std::getline(fileReader, currentLine))
		{
			if (currentLine.compare(0, 2, "v ") == 0)
			{
				Vec3 vertex;
				sscanf_s(currentLine.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				
				m_meshes[lastIndex].vertex.push_back(vertex);
			}

			if (currentLine.compare(0, 2, "f ") == 0)
			{
				Face face;
				Face tex;
				Face normal;

				switch (type)
				{
				case formatOBJ::fvvv:
					sscanf_s(currentLine.c_str(), "f %d %d %d", &face.a, &face.b, &face.c);
					m_meshes[lastIndex].faceIndex.push_back(face);
					break;

				case formatOBJ::fvtn:				
					sscanf_s(currentLine.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
						&face.a, &tex.a, &normal.a,
						&face.b, &tex.b, &normal.b,
						&face.c, &tex.c, &normal.c
					);
					m_meshes[lastIndex].faceIndex.push_back(face);
					break;
				}
			}
		}
	}
	else 
	{
		std::string exceptionMessage = "meshe not found : ";
		exceptionMessage += path;
		throw std::invalid_argument(exceptionMessage);
	}
}

std::vector<Mesh>& Scene::getMeshes() noexcept
{
	return m_meshes;
}