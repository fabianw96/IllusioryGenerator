#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include <array>
#include "Material.h"
#include "MeshLoader.h"
#include "SceneComponent.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class MeshComponent : public SceneComponent
{
public:
	MeshComponent(const char* path, std::shared_ptr<Shader> shader) : m_Shader(shader)
	{
		loadModel(path);
	}

	std::vector<Texture> m_textures_loaded;

	void Draw();
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