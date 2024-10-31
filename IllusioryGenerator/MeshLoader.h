#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "Shader.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class MeshLoader
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	MeshLoader(std::vector<Vertex> verts, std::vector<unsigned int> inds, std::vector<Texture> texts, const std::shared_ptr<Shader>& shader);
	~MeshLoader();
	void RenderMesh();
private:
	unsigned int            VBO, VAO, EBO;
	void                    setupMesh();
	std::shared_ptr<Shader> m_Shader;

};

#endif
