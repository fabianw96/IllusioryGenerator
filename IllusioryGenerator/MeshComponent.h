#pragma once
#include <array>
#include <vector>

#include "Material.h"
#include "SceneComponent.h"
#include "Primitives.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
};

class MeshComponent : public SceneComponent
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	MeshComponent(std::vector<Vertex> verts, std::vector<unsigned int> inds, std::vector<Texture> texts, const std::shared_ptr<Shader>& shader);
	~MeshComponent();
	void RenderMesh();
private:
	unsigned int VBO, VAO, EBO;
	void setupMesh();
	std::shared_ptr<Shader> m_Shader;
};
