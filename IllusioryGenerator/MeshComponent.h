#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include <array>
#include "MeshLoader.h"
#include "SceneComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <glm/ext/matrix_transform.hpp>

#include "TextureLoader.h"

class MeshComponent : public SceneComponent
{
public:
	MeshComponent(const char* path, std::shared_ptr<Shader> shader) : m_Shader(shader)
	{
		loadModel(path);
	}

	std::vector<Texture> m_textures_loaded;

	void Draw();
	void SetPositionAndScale(const std::shared_ptr<ViewPortCamera>& viewPortCamera, glm::vec3 scale) override;
private:
	std::vector<MeshLoader> m_meshes;
	std::string m_directory;
	std::shared_ptr<Shader> m_Shader;


	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	MeshLoader processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif